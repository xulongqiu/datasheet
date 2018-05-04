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
#include <linux/amlogic/aml_gpio_consumer.h>
#include <linux/amlogic/gpio-amlogic.h>
#include <mach/pm.h>

#define LED_UI_DRIVER 1
#define I2C_ERROR_CNT_MAX  2

/* do not change it */
#define AW9110_REG_MAX  0x7f
#define MAX_BUFFER_SIZE 28
#define AW9110_CMD_MAGIC 'k'
#define AW9110_CMD_RESET _IO(AW9110_CMD_MAGIC, 0x80)
#define AW9110_CMD_PWR _IOW(AW9110_CMD_MAGIC, 0x81, int)0)

struct aw9110_i2c_dev {
    struct mutex read_mutex;
    struct i2c_client* client;
    struct miscdevice aw9110_i2c_device;
#if LED_UI_DRIVER
    struct timer_list timer;
#endif
    char* buf;
};

#ifdef LED_UI_DRIVER
static int aw9110_2_write_reg(unsigned char reg, unsigned char  value, struct aw9110_i2c_dev* dev)
{
    int ret = 0;
    static unsigned int err_cnt = 0;

    if (err_cnt > I2C_ERROR_CNT_MAX) {
        return -1;
    }

    dev->buf[0] = reg;
    dev->buf[1] = value;
    mutex_lock(&dev->read_mutex);
    ret = i2c_master_send(dev->client, dev->buf, 2);
    mutex_unlock(&dev->read_mutex);

    if (ret != 2) {
        err_cnt++;
        dev_err(&dev->client->dev, "aw9110_write_reg error, err_cnt=%d\n", err_cnt);
        return ret;
    }

    err_cnt = 0;
    return ret;
}

static int aw9110_dev2_init(struct aw9110_i2c_dev* dev)
{
    //reset
    aw9110_2_write_reg(0x7f, 0, dev);
    //out
    aw9110_2_write_reg(4, 0, dev);
    aw9110_2_write_reg(5, 0, dev);
    //led mode
    aw9110_2_write_reg(0x12, 0, dev);
    aw9110_2_write_reg(0x13, 0, dev);
    //off breath
    aw9110_2_write_reg(0x14, 0, dev);

    return 0;
}

static void aw9110_timer_sr_2(unsigned long data)
{
    struct aw9110_i2c_dev* dev = (struct aw9110_i2c_dev*)data;

    aw9110_dev2_init(dev);
	 del_timer(&dev->timer);
}

#endif

static int aw9110_dev_open(struct inode* inode, struct file* filp)
{
    struct aw9110_i2c_dev* dev = container_of(filp->private_data,
                                              struct aw9110_i2c_dev, aw9110_i2c_device);
    dev_info(&dev->client->dev, "device node major=%d,minor=%d",
             imajor(inode), iminor(inode));
    filp->private_data = dev;
    return 0;
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

    mutex_lock(&dev->read_mutex);
    ret = i2c_master_recv(dev->client, dev->buf, count);
    mutex_unlock(&dev->read_mutex);

    if (ret != count) {
        dev_err(&dev->client->dev, "failed read, rtn=%d\n", ret);
        ret = -EIO;
        return ret;
    } else {
        //dev_info(&dev->client->dev, "read %d bytes -->%02x,%02x,%02x\n",
        // (int)count, dev->buf[0], dev->buf[1], dev->buf[2]);
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

    if (count > MAX_BUFFER_SIZE) {
        dev_err(&dev->client->dev, "request write count=%d\n", (int)count);
        count = MAX_BUFFER_SIZE;
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
    } else {
        //dev_info(&dev->client->dev, "write %d bytes:%02x,%02x,%02x",
        //(int)count, dev->buf[0], dev->buf[1], dev->buf[2]);
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
    int len;                    //need init

    dev_info(&client->dev, "aw9110_led_2:probing aw9110 flags=%x\n", client->flags);

    addr = of_get_property(client->dev.of_node, "reg", &len);
    //printk("addr=0x%02x\n", be32_to_cpup(addr));
    //printk("node name = %s\n", client->dev.of_node->full_name);

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

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        dev_err(&client->dev, "need I2C_FUNC_I2C");
        ret = -ENODEV;
        goto err_buf_kzalloc;
    }

    dev->client = client;

    mutex_init(&dev->read_mutex);
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
    dev_info(&client->dev, "aw9110_led_2:probling aw9110 i2c driver successfully\n");
#if LED_UI_DRIVER
    setup_timer(&dev->timer, aw9110_timer_sr_2, (unsigned long)dev) ;
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(arc_param->led_delay_ms));
#endif

    return 0;

err_misc_register:
    mutex_destroy(&dev->read_mutex);
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
    printk("aw9110_2_suspend\n");
    dev = i2c_get_clientdata(client);

    return 0;
}
static int aw9110_resume(struct i2c_client* client)
{
    struct aw9110_i2c_dev* dev;
    printk("aw9110_2_resume\n");
    dev = i2c_get_clientdata(client);
#ifdef LED_UI_DRIVER
    aw9110_dev2_init(dev);
#endif
    return 0;
}

static const struct i2c_device_id aw9110_i2c_id[] = {
//  {"aw9110_1_led", 0},
    {"aw9110_2_led", 0},
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
        .name = "aw9110_led_2",
    }
};

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
