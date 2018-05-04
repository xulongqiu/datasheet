/*
 * Copyright (C) 2016 XiaoniaoTingting Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Gerneral Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/amlogic/aml_gpio_consumer.h>
#include <linux/amlogic/gpio-amlogic.h>
#include <mach/pm.h>
#include <linux/delay.h>


//#define LED_UI_DRIVER 1
#define I2C_ERROR_CNT_MAX  3

/* do not change it */
#define AW9110_REG_MAX  0x7f
#define MAX_BUFFER_SIZE 28
#define AW9110_CMD_MAGIC 'k'
#define AW9110_CMD_RESET _IO(AW9110_CMD_MAGIC, 0x80)
#define AW9110_CMD_PWR _IOW(AW9110_CMD_MAGIC, 0x81, int)

struct aw9110_i2c_dev {
    struct mutex read_mutex;
    struct i2c_client* client;
    struct miscdevice aw9110_i2c_device;
#if LED_UI_DRIVER
    struct timer_list timer;
    struct work_struct work_update;
    bool   setup;
#endif
    unsigned int int_pin;
    unsigned int sdb_pin;
    char* buf;
    int error_cnt;
};

static int aw9110_write_local(struct aw9110_i2c_dev* dev, unsigned char reg, const unsigned char* buf, unsigned char cnt)
{
    int ret = 0;
    uint8_t tries = 2;

    if (dev->error_cnt > I2C_ERROR_CNT_MAX || cnt > (MAX_BUFFER_SIZE - 1)) {
        return -1;
    }

    dev->buf[0] = reg;
    memcpy(&dev->buf[1], buf, cnt);
    mutex_lock(&dev->read_mutex);
    while(tries > 0){
        ret = i2c_master_send(dev->client, dev->buf, cnt + 1);
        if(ret == (cnt + 1)){
            break;
        }
        dev_err(&dev->client->dev, "aw9110_write_local bus busy, tries=%d\n", tries);
        msleep(2);
        tries--;
    }
    mutex_unlock(&dev->read_mutex);

    if (ret != (cnt + 1)) {
        dev->error_cnt++;
        dev_err(&dev->client->dev, "aw9110_write_local error, dev->error_cnt=%d, ret=%d\n", dev->error_cnt, ret);
        return ret;
    }

    dev->error_cnt = 0;
    return ret;

}

static int aw9110_write_reg(unsigned char reg, unsigned char  value, struct aw9110_i2c_dev* dev)
{
    return aw9110_write_local(dev, reg, &value, 1);
}

static int aw9110_dev_init(struct aw9110_i2c_dev* dev)
{
    /* init the aw9110, set outpur direction & high level*/
    dev_info(&dev->client->dev, "%s:set sdb_pin", __FUNCTION__);
    gpio_direction_output(dev->sdb_pin, 1);
#if LED_UI_DRIVER
    //reset
    aw9110_write_reg(0x7f, 0, dev);
    //out
    aw9110_write_reg(4, 0, dev);
    aw9110_write_reg(5, 0, dev);
    //led mode
    aw9110_write_reg(0x12, 0, dev);
    aw9110_write_reg(0x13, 0, dev);
    //off breath
    aw9110_write_reg(0x14, 0, dev);
#endif
    return 0;
}


#if LED_UI_DRIVER
#define SPIN_LEV_1  1
#define SPIN_LEV_2  4
#define SPIN_LEV_3  8
#define SPIN_LEV_4  16
#define SPIN_LEV_5  64
#define SPIN_LEV_6  255

static const unsigned char led_circle_table[10][10] = {
    {SPIN_LEV_5, SPIN_LEV_6, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0},
    {SPIN_LEV_4, SPIN_LEV_5, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, SPIN_LEV_6},
    {SPIN_LEV_3, SPIN_LEV_4, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5},
    {SPIN_LEV_2, SPIN_LEV_3, SPIN_LEV_1, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4},
    {SPIN_LEV_1, SPIN_LEV_2, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3},
    {0, SPIN_LEV_1, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2},
    {0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1},
    {0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0},
    {0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0},
    {SPIN_LEV_6, 0, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0},
};

static void update_work_func(struct work_struct* work)
{
    struct aw9110_i2c_dev* dev = container_of(work, struct aw9110_i2c_dev, work_update);
    static unsigned char index = 0;

    if (!(dev->setup)) {
        aw9110_dev_init(dev);
        dev->setup = true;
    }

    if(aw9110_write_local(dev, 0x20, led_circle_table[index], 10) < 0){
        return;
    }
    index = (++index) % 10;
}

static void aw9110_timer_sr(unsigned long data)
{
    struct aw9110_i2c_dev* dev = (struct aw9110_i2c_dev*)data;
    schedule_work(&(dev->work_update));
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(100));
}

#endif

static int aw9110_dev_open(struct inode* inode, struct file* filp)
{
    struct aw9110_i2c_dev* dev = container_of(filp->private_data,
                                              struct aw9110_i2c_dev, aw9110_i2c_device);
    dev_info(&dev->client->dev, "device node major=%d,minor=%d",
             imajor(inode), iminor(inode));
    filp->private_data = dev;
#if LED_UI_DRIVER
    del_timer_sync(&dev->timer);
    flush_work(&dev->work_update);
    cancel_work_sync(&dev->work_update);
#endif
    return aw9110_dev_init(dev);
}

static ssize_t aw9110_dev_read(struct file* filp, char __user* buf,
                               size_t count, loff_t* offset)
{
    struct aw9110_i2c_dev* dev = filp->private_data;
    int ret = 0;

    if (count > MAX_BUFFER_SIZE) {
        dev_err(&dev->client->dev, "request read count=%d\n", (int)count);
        count = MAX_BUFFER_SIZE;
    }

    if ((buf[0] + count) > AW9110_REG_MAX) {
        dev_err(&dev->client->dev, "aw9110 max address=%d\n", AW9110_REG_MAX);
        return -ENXIO;
    }

    mutex_lock(&dev->read_mutex);
    ret = i2c_master_recv(dev->client, dev->buf, count);
    mutex_unlock(&dev->read_mutex);

    if (ret != count) {
        dev_err(&dev->client->dev, "failed read, rtn=%d\n", ret);
        ret = -EIO;
        return ret;
    } else {
        // dev_info(&dev->client->dev, "read %d bytes -->%02x,%02x,%02x\n",
        //        (int)count, dev->buf[0], dev->buf[1], dev->buf[2]);
    }

    if (copy_to_user(buf, dev->buf, count)) {
        dev_err(&dev->client->dev, "failed to copy to user\n");
        ret = -EFAULT;
    }

    return ret;
}

static ssize_t aw9110_dev_write(struct file* filp, const char __user* buf,
                                size_t count, loff_t* offset)
{
    struct aw9110_i2c_dev* dev = filp->private_data;
    int ret = 0;

    if (dev->error_cnt > I2C_ERROR_CNT_MAX){
        return -EIO;
    }

    if (count > MAX_BUFFER_SIZE) {
        dev_err(&dev->client->dev, "request write count=%d\n", (int)count);
        count = MAX_BUFFER_SIZE;
    }

    if ((buf[0] + count) > AW9110_REG_MAX) {
        dev_err(&dev->client->dev, "aw9110 max address=%d\n", AW9110_REG_MAX);
        return -ENXIO;
    }

    if ((ret = copy_from_user(dev->buf, buf, count)) != 0) {
        dev_err(&dev->client->dev, "copy from user error,rtn=%d\n", ret);
        return -EFAULT;
    }

    mutex_lock(&dev->read_mutex);
    ret = i2c_master_send(dev->client, dev->buf, count);
    mutex_unlock(&dev->read_mutex);

    if (ret != count) {
        dev_err(&dev->client->dev, "request write error,count=%d\n", ret);
        ret = -EIO;
        if(++dev->error_cnt > I2C_ERROR_CNT_MAX){
            dev_err(&dev->client->dev, "request write error many times(%d)\n", dev->error_cnt);
        }
    } else {
        dev->error_cnt = 0;
//    dev_info(&dev->client->dev, "write %d bytes:%02x,%02x,%02x",
        //           (int)count, dev->buf[0], dev->buf[1], dev->buf[2]);
    }

    return ret;
}

static long aw9110_dev_unlocked_ioctl(struct file* filp,
                                      unsigned int cmd, unsigned long arg)
{
    struct aw9110_i2c_dev* dev = filp->private_data;
    int ret = 0;
    int rtn = 0;

    switch (cmd) {
    case AW9110_CMD_RESET:
        dev->buf[0] = 0x7f;
        dev->buf[1] = 0x00;
        mutex_lock(&dev->read_mutex);
        ret = i2c_master_send(dev->client, dev->buf, 2);
        mutex_unlock(&dev->read_mutex);

        if (ret != 2) {
            dev_err(&dev->client->dev, "aw9100 reset fail\n");
            rtn = -1;
        }

        break;

    case AW9110_CMD_PWR:
        gpio_set_value(dev->sdb_pin, arg);
        break;

    default:
        dev_err(&dev->client->dev, "unknown cmd (%x, %lx)\n", cmd, arg);
        return -1;
    }

    return rtn;
}

static const struct file_operations aw9110_dev_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
    .read = aw9110_dev_read,
    .write = aw9110_dev_write,
    .open = aw9110_dev_open,
    .unlocked_ioctl = aw9110_dev_unlocked_ioctl
};

static int aw9110_probe(struct i2c_client* client,
                        const struct i2c_device_id* id)
{
    int ret = 0;
    struct aw9110_i2c_dev* dev; //need init
    const __be32* addr;         //need init
    unsigned int gpio;          //need init
    const char* str;            //need init
    int len;                    //need init

    dev_info(&client->dev, "aw9110_led_1:probing aw9110 flags=%x\n",client->flags);

    addr = of_get_property(client->dev.of_node, "reg", &len);
    //printk("addr=0x%02x\n", be32_to_cpup(addr));
    //printk("node name = %s\n", client->dev.of_node->full_name);


    ret = of_property_read_string(client->dev.of_node, "gpio_sdb_pin", &str);

    if (ret) {
        printk(KERN_WARNING "not get gpio_led_sdb\n");
        return -ENODEV;
    } else {
        gpio = amlogic_gpio_name_map_num(str);
    }

    //printk("gpio = %d\n", gpio);

    if (!gpio_is_valid(gpio)) {
        pr_err("%s: invalid GPIO pins, sdb=%d\n", client->dev.of_node->full_name, gpio);
        return -ENODEV;
    }

    dev = kzalloc(sizeof(*dev), GFP_KERNEL);

    if (dev == NULL) {
        dev_err(&client->dev, "failed to allocate memory for module data\n");
        ret = -ENOMEM;
        goto err_exit;
    }

    dev->buf = kzalloc(MAX_BUFFER_SIZE, GFP_KERNEL);

    if (dev->buf == NULL) {
        dev_err(&client->dev, "failed to allocate memory for rw data\n");
        ret = -ENOMEM;
        goto err_buf_kzalloc;
    }

    dev->sdb_pin = gpio;
    ret = gpio_request(dev->sdb_pin, "sdb");

    if (ret) {
        if (ret == -EINVAL) {
            ret = -EPROBE_DEFER;
        }

        goto err_request_sdb;
    }

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        dev_err(&client->dev, "need I2C_FUNC_I2C");
        ret = -ENODEV;
        goto err_request_sdb;
    }

    dev->client = client;
    mutex_init(&dev->read_mutex);
    gpio_direction_output(dev->sdb_pin, 1);
    msleep(5);
    if(aw9110_write_reg(0x7f, 0, dev) < 0){
        dev_err(&client->dev, "reset aw9110 error\n");
        ret = -EINVAL;
        goto err_misc_register;
    }
    gpio_direction_output(dev->sdb_pin, 0);


    dev->aw9110_i2c_device.minor = MISC_DYNAMIC_MINOR;
    /* need to be debug */
    dev->aw9110_i2c_device.name = of_get_property(client->dev.of_node, "dev_name", &len);
    //printk("aw9110_device.name=%s\n", dev->aw9110_i2c_device.name);
    dev->aw9110_i2c_device.fops = &aw9110_dev_fops;

    ret = misc_register(&dev->aw9110_i2c_device);

    if (ret) {
        dev_err(&client->dev, "misc_register failed");
        goto err_misc_register;
    }

    //dev_info(&client->dev, "client address:%x\n", client->addr);

    i2c_set_clientdata(client, dev);
#if LED_UI_DRIVER
    dev->setup = false;
    INIT_WORK(&(dev->work_update), update_work_func);
    setup_timer(&dev->timer, aw9110_timer_sr, (unsigned long)dev) ;
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(arc_param->led_delay_ms));
#endif
    dev_info(&client->dev, "aw9110_led_1:probling aw9110 i2c driver successfully\n");
    return 0;

err_misc_register:
    mutex_destroy(&dev->read_mutex);
err_request_sdb:
    gpio_free(dev->sdb_pin);
err_buf_kzalloc:
    kfree(dev->buf);
err_exit:
    kfree(dev);

    return ret;
}

static int aw9110_remove(struct i2c_client* client)
{
    struct aw9110_i2c_dev* dev;

    dev = i2c_get_clientdata(client);
    misc_deregister(&dev->aw9110_i2c_device);
    mutex_destroy(&dev->read_mutex);
#if LED_UI_DRIVER
    del_timer_sync(&dev->timer);
    flush_work(&dev->work_update);
    cancel_work_sync(&dev->work_update);
#endif

    if (dev->buf != NULL) {
        kfree(dev->buf);
    }

    if (dev != NULL) {
        kfree(dev);
    }

    return 0;
}

static int aw9110_suspend(struct i2c_client* client, pm_message_t mesg)
{
    struct aw9110_i2c_dev* dev;
    printk("aw9110_1_suspend\n");
    dev = i2c_get_clientdata(client);
#if LED_UI_DRIVER
    del_timer_sync(&dev->timer);
#endif
    gpio_direction_output(dev->sdb_pin, 0);

    return 0;
}
static int aw9110_resume(struct i2c_client* client)
{
    struct aw9110_i2c_dev* dev;
    printk("aw9110_1_resume\n");
    dev = i2c_get_clientdata(client);
    aw9110_dev_init(dev);
#if 0//after resume, do not show circle ui any more
    dev->setup = false;
    setup_timer(&dev->timer, aw9110_timer_sr, (unsigned long)dev);
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(arc_param->led_delay_ms));
#endif
    return 0;
}

static const struct i2c_device_id aw9110_i2c_id[] = {
    {"aw9110_1_led", 0},
    {}
};

static struct i2c_driver aw9110_i2c_driver = {
    .id_table = aw9110_i2c_id,
    .probe = aw9110_probe,
    .remove = aw9110_remove,
    .suspend = aw9110_suspend,
    .resume = aw9110_resume,
    .driver = {
        .owner = THIS_MODULE,
        .name = "aw9110_led_1",
    }
};
#if LED_UI_DRIVER
static int __init get_circle_ui_delay(char* str)
{
    int result = 0;

    if (str == NULL || *str < '0' || *str > '9') {
        arc_param->led_delay_ms = 100;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str++ - '0');
    }

    if (result > 0) {
        arc_param->led_delay_ms = result;
    } else {
        arc_param->led_delay_ms = 100;
    }

    printk("aw9110:led_delay_ms=%d\n", arc_param->led_delay_ms);

    return 0;
}

__setup("circle_ui_delay=", get_circle_ui_delay);
#endif


/* module load/unload*/

static int __init aw9110_driver_init(void)
{
    printk("aw9110_driver_init\n");
    return i2c_add_driver(&aw9110_i2c_driver);
}

static void __exit aw9110_driver_exit(void)
{
    printk("aw9110_driver_exit\n");
    return i2c_del_driver(&aw9110_i2c_driver);
}

module_init(aw9110_driver_init);
module_exit(aw9110_driver_exit);

MODULE_AUTHOR("XiaoniaoTingting");
MODULE_DESCRIPTION("aw9110 i2c driver");
MODULE_LICENSE("GPL");

