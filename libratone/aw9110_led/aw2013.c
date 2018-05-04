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

#define LED_UI_DRIVER 0
#define I2C_ERROR_CNT_MAX  10

/* do not change it */
#define aw2013_REG_MAX  0x7f
#define MAX_BUFFER_SIZE 28

struct aw2013_i2c_dev {
    struct mutex read_mutex;
    struct i2c_client* client;
    struct miscdevice aw2013_i2c_device;
#if LED_UI_DRIVER
    struct timer_list timer;
#endif
    char* buf;
    uint16_t i2c_error_cnt;
    uint8_t ctrl_by_user;
};

static struct aw2013_i2c_dev* g_dev = NULL;

static ssize_t aw2013_dev_write_local(uint8_t reg, uint8_t value)
{
    int ret = 0;

    if (g_dev == NULL || g_dev->i2c_error_cnt > I2C_ERROR_CNT_MAX) {
        return -1;
    }

    g_dev->buf[0] = reg;
    g_dev->buf[1] = value;
    mutex_lock(&g_dev->read_mutex);
    ret = i2c_master_send(g_dev->client, g_dev->buf, 2);
    mutex_unlock(&g_dev->read_mutex);

    if (ret != 2) {
        dev_err(&g_dev->client->dev, "aw2013, failed to write reg(%02x)value(%02x) return %d\n", reg, value, ret);

        if (++g_dev->i2c_error_cnt >= I2C_ERROR_CNT_MAX) {
            dev_err(&g_dev->client->dev, "aw2013, failed many times, may device lost\n");
        }

        return -EIO;
    }

    g_dev->i2c_error_cnt = 0;
    return ret;
}

static ssize_t aw2013_dev_read_local(int reg, char* buf, ssize_t count)
{
    char reg_buf[2];
    int ret = count;

    if (g_dev == NULL || g_dev->i2c_error_cnt > I2C_ERROR_CNT_MAX) {
        return ret;
    }

    mutex_lock(&g_dev->read_mutex);
    reg_buf[0] = reg;
    ret = i2c_master_send(g_dev->client, reg_buf, 1);

    ret = i2c_master_recv(g_dev->client, buf, count);
    mutex_unlock(&g_dev->read_mutex);

    if (ret != count) {
        dev_err(&g_dev->client->dev, "aw2013, failed to read reg(%02x) return %d\n", reg, ret);

        if (++g_dev->i2c_error_cnt >= I2C_ERROR_CNT_MAX) {
            dev_err(&g_dev->client->dev, "aw2013, failed many times, may device lost\n");
        }

        return -EIO;
    }

    g_dev->i2c_error_cnt = 0;

    return ret;
}

static int aw2013_dev_init(void)
{
    //reset
    aw2013_dev_write_local(0x00, 0x55);
    //GCR.0, enable led
    aw2013_dev_write_local(0x01, 0x01);
    //LCTR.[0,1,2], on every led
    aw2013_dev_write_local(0x30, 0x07);
    //LCFG[0,1,2], mode.4:pwm(0), blink(1); current[0,1]: 5mA max
    aw2013_dev_write_local(0x31, 0x01);
    aw2013_dev_write_local(0x32, 0x01);
    aw2013_dev_write_local(0x33, 0x01);
    //PW4yyM[0,1,2], light level, 0..255
    aw2013_dev_write_local(0x34, 0);
    aw2013_dev_write_local(0x35, 0);
    aw2013_dev_write_local(0x36, 0);
    //LEDxT0T1:fade in[4..6], light[0..2]
    aw2013_dev_write_local(0x37, 0);
    aw2013_dev_write_local(0x3A, 0);
    aw2013_dev_write_local(0x3D, 0);
    //LEDxT2T3:fade out[4..6], dark[0..2]
    aw2013_dev_write_local(0x38, 0);
    aw2013_dev_write_local(0x3B, 0);
    aw2013_dev_write_local(0x3E, 0);
    //delay[4..7], repeat[0..3], right now, no autostop
    aw2013_dev_write_local(0x39, 0);
    aw2013_dev_write_local(0x3C, 0);
    aw2013_dev_write_local(0x3F, 0);

    return 0;
}

int aw2013_charing_ui(int status)
{
    uint8_t lvl = 0;

    if (g_dev == NULL || g_dev->ctrl_by_user != 0) {
        return 0;
    }

    if (status != 0) {
        lvl = 255;
    }

    aw2013_dev_init();
    //PW4yyM[0,1,2], light level, 0..255
    aw2013_dev_write_local(0x34, 0);
    aw2013_dev_write_local(0x35, 0);
    aw2013_dev_write_local(0x36, lvl);
    return 0;
}
EXPORT_SYMBOL(aw2013_charing_ui);

#if LED_UI_DRIVER
static void aw2013_timer(unsigned long data)
{
    struct aw2013_i2c_dev* dev = (struct aw2013_i2c_dev*)data;

    aw2013_dev_init();
    del_timer(&dev->timer);
}

#endif

typedef struct aw2013_dump_regs {
    const char* name;
    uint8_t addr;
} aw2013_dump_regs_t;

static int aw2013_regs_dump(char* buf)
{
    aw2013_dump_regs_t aw2013_regs[] = {
        {NULL, 0}
    };
    int size = 0;
    int i = 0;
    uint8_t val = 0;

    for (i = 0; aw2013_regs[i].name != NULL; i++) {
        if (aw2013_dev_read_local(aw2013_regs[i].addr, &val, 1) == 2) {
            if (buf == NULL) {
                printk("%s(%02x)=%02x\n", aw2013_regs[i].name, aw2013_regs[i].addr, val);
            } else {
                size += sprintf(&buf[size], "%s(%02x)=%02x\n", aw2013_regs[i].name, aw2013_regs[i].addr, val);
            }
        }
    }

    return size;
}

static int aw2013_dev_open(struct inode* inode, struct file* filp)
{
    struct aw2013_i2c_dev* dev = container_of(filp->private_data,
                                              struct aw2013_i2c_dev, aw2013_i2c_device);
    dev_info(&dev->client->dev, "device node major=%d,minor=%d",
             imajor(inode), iminor(inode));
    filp->private_data = dev;
    dev->ctrl_by_user = 1;
    return 0;
}

static ssize_t aw2013_dev_read(struct file* filp, char __user* buf,
                               size_t count, loff_t* offset)
{
    struct aw2013_i2c_dev* dev = filp->private_data;
    int ret = 0;

    if (dev == NULL || dev->i2c_error_cnt > I2C_ERROR_CNT_MAX) {
        return ret;
    }

    if (count > MAX_BUFFER_SIZE) {
        dev_err(&dev->client->dev, "request read count=%d\n", (int)count);
        count = MAX_BUFFER_SIZE;
    }

    mutex_lock(&dev->read_mutex);
    ret = i2c_master_recv(dev->client, dev->buf, count);
    mutex_unlock(&dev->read_mutex);

    if (ret != count) {
        dev_err(&dev->client->dev, "failed read, rtn=%d\n", ret);

        if (++dev->i2c_error_cnt >= I2C_ERROR_CNT_MAX) {
            dev_err(&dev->client->dev, "aw2013, failed many times, may device lost\n");
        }

        return -EIO;
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

static ssize_t aw2013_dev_write(struct file* filp, const char __user* buf,
                                size_t count, loff_t* offset)
{
    struct aw2013_i2c_dev* dev = filp->private_data;
    int ret = 0;

    if (dev == NULL || dev->i2c_error_cnt > I2C_ERROR_CNT_MAX) {
        return ret;
    }

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

        if (++dev->i2c_error_cnt >= I2C_ERROR_CNT_MAX) {
            dev_err(&dev->client->dev, "aw2013, failed many times, may device lost\n");
        }

        return -EIO;
    } else {
        //dev_info(&dev->client->dev, "write %d bytes:%02x,%02x,%02x",
        //(int)count, dev->buf[0], dev->buf[1], dev->buf[2]);
    }

    return ret;
}

static long aw2013_dev_unlocked_ioctl(struct file* filp,
                                      unsigned int cmd, unsigned long arg)
{
    struct aw2013_i2c_dev* dev = filp->private_data;
    int rtn = 0;

    switch (cmd) {
    default:
        dev_err(&dev->client->dev, "unknown cmd (%x, %lx)\n", cmd, arg);
        return -1;
    }

    return rtn;
}

static const struct file_operations aw2013_dev_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
    .read = aw2013_dev_read,
    .write = aw2013_dev_write,
    .open = aw2013_dev_open,
    .unlocked_ioctl = aw2013_dev_unlocked_ioctl
};

static ssize_t aw2013_regs_store(struct device* dev, struct device_attribute* attr, const char* input, size_t size)
{
    uint32_t reg = 0, val = 0;

    if (input == NULL || size <= 0) {
        pr_err("[%s]: error size=%d\n", __func__, size);
        return size;
    }

    if (sscanf(input, "%x %x", &reg, &val) != 2) {
        pr_err("[%s]: echo reg(02x) val(02x) > aw2013_regs\n", __func__);
        return -EINVAL;
    }

    if (reg > 0xff || val > 0xffff) {
        pr_err("[%s]: reg <= 0xff, val <= 0xffff \n", __func__);
        return -EINVAL;
    }

    if (aw2013_dev_write_local((uint8_t)reg, (uint8_t)val) < 0) {
        pr_err("[%s]: write reg(%02x)=%02x error\n", __func__, reg, val);
        return -EINVAL;
    } else {
        printk("[%s]: write reg(%02x)=%02x succ\n", __func__, reg, val);
    }

    return size;
}

static ssize_t aw2013_regs_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    if (buf == NULL) {
        pr_err("[%s]: error buf == NULL\n", __func__);
        return 0;
    }

    return aw2013_regs_dump(buf);
}

// Define our device attributes to export them to sysfs
static DEVICE_ATTR(aw2013_regs, S_IRWXU | S_IRWXG | S_IROTH, aw2013_regs_show, aw2013_regs_store);

static struct attribute* aw2013_sysfs_attrs[] = {
    &dev_attr_aw2013_regs.attr,
    NULL
};

static struct attribute_group aw2013_sysfs_attr_grp = {
    .name = "control",
    .attrs = aw2013_sysfs_attrs,
};

void aw2013_Sysfs_Init(struct aw2013_i2c_dev* aw2013_dev)
{
    short ret = 0;

    if (aw2013_dev  == NULL) {
        pr_err("%s - aw2013_dev is null!\n", __func__);
        return;
    }

    /* create attribute group for accessing the aw2013 */
    ret = sysfs_create_group(&aw2013_dev->client->dev.kobj, &aw2013_sysfs_attr_grp);

    if (ret) {
        pr_err("aw2013 %s - Error creating sysfs attributes!\n", __func__);
    }
}

static int aw2013_probe(struct i2c_client* client,
                        const struct i2c_device_id* id)
{
    int ret = 0;
    struct aw2013_i2c_dev* dev; //need init
    const __be32* addr;         //need init
    int len;                    //need init

    dev_info(&client->dev, "aw2013_led:probing aw2013 flags=%x\n", client->flags);

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
    dev->aw2013_i2c_device.minor = MISC_DYNAMIC_MINOR;
    /* need to be debug */
    dev->aw2013_i2c_device.name = of_get_property(client->dev.of_node, "dev_name", &len);
    //printk("aw2013_device.name=%s\n", dev->aw2013_i2c_device.name);
    dev->aw2013_i2c_device.fops = &aw2013_dev_fops;

    ret = misc_register(&dev->aw2013_i2c_device);

    if (ret) {
        dev_err(&client->dev, "misc_register failed");
        goto err_misc_register;
    }

    //dev_info(&client->dev, "client address:%x\n", client->addr);

    i2c_set_clientdata(client, dev);
    dev_info(&client->dev, "aw2013_led:probling aw2013 i2c driver successfully\n");
#if LED_UI_DRIVER
    setup_timer(&dev->timer, aw2013_timer, (unsigned long)dev) ;
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(arc_param->led_delay_ms));
#endif
    dev->ctrl_by_user = 0;
    aw2013_Sysfs_Init(dev);
    g_dev = dev;
    return 0;

err_misc_register:
    mutex_destroy(&dev->read_mutex);
err_buf_kzalloc:
    kfree(dev->buf);
err_exit:
    kfree(dev);

    return ret;
}

static int aw2013_remove(struct i2c_client* client)
{
    struct aw2013_i2c_dev* dev;

    dev = i2c_get_clientdata(client);
    misc_deregister(&dev->aw2013_i2c_device);
    mutex_destroy(&dev->read_mutex);

    if (dev->buf != NULL) {
        kfree(dev->buf);
    }

    if (dev != NULL) {
        kfree(dev);
    }

    g_dev = NULL;

    return 0;
}

static int aw2013_suspend(struct i2c_client* client, pm_message_t mesg)
{
    struct aw2013_i2c_dev* dev;
    printk("aw2013_suspend\n");
    dev = i2c_get_clientdata(client);

    return 0;
}
static int aw2013_resume(struct i2c_client* client)
{
    struct aw2013_i2c_dev* dev;
    printk("aw2013_resume\n");
    dev = i2c_get_clientdata(client);
    return 0;
}

static const struct i2c_device_id aw2013_i2c_id[] = {
    {"aw2013_led", 0},
    {}
};

static struct i2c_driver aw2013_i2c_driver = {
    .id_table = aw2013_i2c_id,
    .probe = aw2013_probe,
    .remove = aw2013_remove,
    .suspend = aw2013_suspend,
    .resume = aw2013_resume,
    .driver = {
        .owner = THIS_MODULE,
        .name = "aw2013_led",
    }
};

/* module load/unload*/

static int __init aw2013_driver_init(void)
{
    printk("aw2013_driver_init\n");
    return i2c_add_driver(&aw2013_i2c_driver);
}

static void __exit aw2013_driver_exit(void)
{
    printk("aw2013_driver_exit\n");
    return i2c_del_driver(&aw2013_i2c_driver);
}

module_init(aw2013_driver_init);
module_exit(aw2013_driver_exit);

MODULE_AUTHOR("XiaoniaoTingting");
MODULE_DESCRIPTION("aw2013 i2c driver");
MODULE_LICENSE("GPL");
