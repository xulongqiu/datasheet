/*
 * Copyright (C) 2012 Broadcom Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/poll.h>
#include <linux/version.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>

struct aw9110_2_i2c_dev {
	struct mutex read_mutex;
	struct i2c_client *client;
	struct miscdevice aw9110_misc_device;
	char * buf;
};

struct aw9110_2_i2c_dev *aw9110_2_dev;

static ssize_t aw9110_2_dev_read_local(int reg, char *buf)
{
	
	char reg_buf[2];
	int ret;
	mutex_lock(&aw9110_2_dev->read_mutex);
	reg_buf[0] = reg;
	ret = i2c_master_send(aw9110_2_dev->client, reg_buf, 1);

	ret = i2c_master_recv(aw9110_2_dev->client, buf, 1);
	//printk("%s %d buf = 0x%x\n",__func__,__LINE__, *buf);
	mutex_unlock(&aw9110_2_dev->read_mutex);
	
	if (ret != 1) 
	{
		dev_err(&aw9110_2_dev->client->dev,
				"failed to read 1 byte return %d\n", ret);
		ret = -EIO;
		return ret;
	}
	else
	{
		//printk("read the reg 0x%x = 0x%x\n", reg, *buf);
	}
	return ret;
}

static ssize_t aw9110_2_dev_write_local(int reg, char *buf) 
{
	int ret;
	char reg_buf[2];
	mutex_lock(&aw9110_2_dev->read_mutex);
	reg_buf[0] = reg;
	reg_buf[1] = *buf;
	ret = i2c_master_send(aw9110_2_dev->client, reg_buf, 2);
	mutex_unlock(&aw9110_2_dev->read_mutex);

	if(ret != 2) 
	{
		printk("fail to write the reg 0x%x\n ", reg);
		ret = -EIO;
	}
	else
	{
		//printk("write the reg 0x%x = 0x%x ok!\n ", reg, reg_buf[1]);
	}
	return ret;
}

void set_aw9110_ext_2_gpio_out(int out_index, int level)
{
	// set as gpio
	char reg, reg_value;
	unsigned char shift_bit;
//CTL
	reg = 0x11;
	aw9110_2_dev_read_local(reg, &reg_value);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | (1<<4);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_2_dev_write_local(reg, &reg_value);
	
	if(out_index > 3) {
		reg = 0x12;
		shift_bit = out_index - 4;
		aw9110_2_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x13;
		shift_bit = out_index;
		aw9110_2_dev_read_local(reg, &reg_value);
	}
	
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | (1<<shift_bit);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_2_dev_write_local(reg, &reg_value);
//=set as output
	if(out_index > 3) {
		reg = 0x04;
		shift_bit = out_index - 4;
		aw9110_2_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x05;
		shift_bit = out_index;
		aw9110_2_dev_read_local(reg, &reg_value);
	}
	
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value & (~(1<<shift_bit));
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_2_dev_write_local(reg, &reg_value);
// set the gpio output level
	if(out_index > 3) {
		reg = 0x02;
		shift_bit = out_index - 4;
		aw9110_2_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x03;
		shift_bit = out_index;
		aw9110_2_dev_read_local(reg, &reg_value);
	}
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	if(level == 0)
		reg_value = reg_value & (~(1<<shift_bit));
	else
		reg_value = reg_value | (1<<shift_bit);
		
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_2_dev_write_local(reg, &reg_value);
}
EXPORT_SYMBOL(set_aw9110_ext_2_gpio_out);

void set_aw9110_ext_2_gpio_in(int in_index)
{
// set as gpio
	char reg, reg_value;
	unsigned char shift_bit;

	if(in_index > 3) {
		reg = 0x12;
		shift_bit = in_index - 4;
		aw9110_2_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x13;
		shift_bit = in_index;
		aw9110_2_dev_read_local(reg, &reg_value);
	}
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | (1<<shift_bit);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_2_dev_write_local(reg, &reg_value);
//=set as input 
	if(in_index > 3) {
		reg = 0x04;
		shift_bit = in_index - 4;
		aw9110_2_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x05;
		shift_bit = in_index;
		aw9110_2_dev_read_local(reg, &reg_value);
	}
	
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | 1<<shift_bit;
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_2_dev_write_local(reg, &reg_value);
}
EXPORT_SYMBOL(set_aw9110_ext_2_gpio_in);

int get_aw9110_ext_2_gpio_in_stat(int in_index)
{
	char reg, reg_value;
	unsigned char shift_bit;

	if(in_index > 3) {
		reg = 0x00;
		shift_bit = in_index - 4;
		aw9110_2_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x01;
		shift_bit = in_index;
		aw9110_2_dev_read_local(reg, &reg_value);
	}

	return reg_value & (1<<shift_bit);
}
EXPORT_SYMBOL(get_aw9110_ext_2_gpio_in_stat);

static int aw9110_2_dev_open(struct inode *inode, struct file *filp)
{
	int ret = 0;

	struct aw9110_2_i2c_dev *aw9110_2_dev = container_of(filp->private_data,
							   struct aw9110_2_i2c_dev,
							   aw9110_misc_device);
	filp->private_data = aw9110_2_dev;
	dev_info(&aw9110_2_dev->client->dev,
		 "device node major=%d, minor=%d\n", imajor(inode), iminor(inode));

	return ret;
}

static long aw9110_2_dev_unlocked_ioctl(struct file *filp,
					 unsigned int cmd, unsigned long arg)
{
	struct aw9110_2_i2c_dev *aw9110_2_dev = filp->private_data;

	switch (cmd) {
	case 0: 
		set_aw9110_ext_2_gpio_out(1, 1);
		break;
	case 1: 
		set_aw9110_ext_2_gpio_out(2, 1);
		break;
	case 3: 
		set_aw9110_ext_2_gpio_out(3, 1);
		break;
	case 4: 
		set_aw9110_ext_2_gpio_out(4, 1);
		break;
	case 5: 
		set_aw9110_ext_2_gpio_out(5, 1);
		break;
	case 6: 
		set_aw9110_ext_2_gpio_out(6, 1);
		break;
	case 7: 
		set_aw9110_ext_2_gpio_out(7, 1);
		break;
	case 8: 
		set_aw9110_ext_2_gpio_out(8, 1);
		break;
	default:
		dev_err(&aw9110_2_dev->client->dev,
			"%s, unknown cmd (%x, %lx)\n", __func__, cmd, arg);
		return 0;
	}

	return 0;
}

static ssize_t aw9110_2_dev_read(struct file *filp, char __user *buf,
				  size_t count, loff_t *offset)
{
	struct aw9110_2_i2c_dev *aw9110_2_dev = filp->private_data;
	int total, len, ret;

	total = 0;
	len = 0;

	if (count > 128)
	{
		dev_err(&aw9110_2_dev->client->dev, "read out of memory %d\n", count);
		count = 128;
	}
	
	mutex_lock(&aw9110_2_dev->read_mutex);
	ret = i2c_master_recv(aw9110_2_dev->client, aw9110_2_dev->buf, count);
	mutex_unlock(&aw9110_2_dev->read_mutex);
	
	if (ret != count) 
	{
			dev_err(&aw9110_2_dev->client->dev,
				"failed to read %d byte return %d\n", count, ret);
			ret = -EIO;

			return ret;
	} /* if */
	else
	{
		printk("%s %d\n",__func__,__LINE__);
	}

	if (copy_to_user(buf, aw9110_2_dev->buf, count)) {
		dev_err(&aw9110_2_dev->client->dev,
			"failed to copy to user space, count = %d\n", count);
		count = -EFAULT;
	}

	return count;
}

static ssize_t aw9110_2_dev_write(struct file *filp, const char __user *buf,
				   size_t count, loff_t *offset)
{
	struct aw9110_2_i2c_dev *aw9110_2_dev = filp->private_data;
	int ret;

	if (count > 128) {
		dev_err(&aw9110_2_dev->client->dev, "write out of memory %d\n", count);
		return -ENOMEM;
	}

	if (copy_from_user(aw9110_2_dev->buf, buf, count)) {
		dev_err(&aw9110_2_dev->client->dev,
			"failed to copy from user space\n");
		return -EFAULT;
	}


	mutex_lock(&aw9110_2_dev->read_mutex);
	ret = i2c_master_send(aw9110_2_dev->client, aw9110_2_dev->buf, count);
	mutex_unlock(&aw9110_2_dev->read_mutex);

	if(ret != count) 
	{
		printk(" error %s %d\n",__func__,__LINE__);
		ret = -EIO;
	}
	else
	{
		printk(" write ok! %s %d\n",__func__,__LINE__);
	}

	return ret;
}

void aw9110_2_init()
{
	printk("index = 0");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(0, 0);
	printk("index = 1");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(1, 1);
	printk("index = 2");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(2, 1);
	printk("index = 3");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(3, 0);
	printk("index = 4");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(4, 1);
	printk("index = 5");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(5, 1);
	printk("index = 6");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(6, 1);
	printk("index = 7");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(7, 1);
	printk("index = 8");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(8, 1);
	printk("index = 9");
	printk("**************************************");
	set_aw9110_ext_2_gpio_out(9, 0);
}

static const struct file_operations aw9110_2_dev_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.read = aw9110_2_dev_read,
	.write = aw9110_2_dev_write,
	.open = aw9110_2_dev_open,
	.unlocked_ioctl = aw9110_2_dev_unlocked_ioctl
};
static int aw9110_2_i2c_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "need I2C_FUNC_I2C\n");
		return -ENODEV;
	}

	aw9110_2_dev = kzalloc(sizeof(*aw9110_2_dev), GFP_KERNEL);
	if (aw9110_2_dev == NULL) {
		dev_err(&client->dev,
			"failed to allocate memory for module data\n");
		ret = -ENOMEM;
		goto err_exit;
	}
	aw9110_2_dev->buf = kzalloc(128, GFP_KERNEL);
	if(aw9110_2_dev->buf == NULL)
	{
		dev_err(&client->dev, "failed to allocate memory for rw buffer\n");
		ret = -ENOMEM;
		goto err_exit1;
	}

	aw9110_2_dev->client = client;
	mutex_init(&aw9110_2_dev->read_mutex);

	aw9110_2_dev->aw9110_misc_device.minor = MISC_DYNAMIC_MINOR;
	aw9110_2_dev->aw9110_misc_device.name = "aw9110_22c";
	aw9110_2_dev->aw9110_misc_device.fops = &aw9110_2_dev_fops;

	ret = misc_register(&aw9110_2_dev->aw9110_misc_device);
	if (ret) {
		printk("misc_register failed\n");
		goto err_misc_register;
	}

	aw9110_2_init();
	dev_info(&client->dev, "%s, saving address %d\n",__func__, client->addr);

	i2c_set_clientdata(client, aw9110_2_dev);
	dev_info(&client->dev,
		 "%s, probing aw9110_2 i2c driver exited successfully\n",
		 __func__);
	return 0;
err_misc_register:
	mutex_destroy(&aw9110_2_dev->read_mutex);
err_exit1:
	kfree(aw9110_2_dev->buf);
err_exit:
	kfree(aw9110_2_dev);
	return ret;
}

static int aw9110_2_i2c_remove(struct i2c_client *client)
{
	struct aw9110_2_i2c_dev *aw9110_2_dev;

	aw9110_2_dev = i2c_get_clientdata(client);
	mutex_destroy(&aw9110_2_dev->read_mutex);

	kfree(aw9110_2_dev);

	return 0;
}

#ifdef CONFIG_PM
static int aw9110_2_i2c_suspend(struct i2c_client* client, pm_message_t mesg)
{
    printk(KERN_INFO "aw9110_2_i2c_suspend..\n");
    return 0;
}

static int aw9110_2_i2c_resume(struct i2c_client* client)
{
	aw9110_2_init();
	printk(KERN_INFO "aw9110_2_i2c_resume..\n");
	return 0;
}


#else
#define aw9110_2_i2c_suspend NULL
#define aw9110_2_i2c_resume NULL
#endif /* CONFIG_PM */

static const struct i2c_device_id aw9110_2_i2c_id[] = {
	{"aw9110_ext_2", 0},
	{}
};

static struct i2c_driver aw9110_2_i2c_driver = {
	.id_table = aw9110_2_i2c_id,
	.probe = aw9110_2_i2c_probe,
	.remove = aw9110_2_i2c_remove,
	.suspend = aw9110_2_i2c_suspend,
   .resume = aw9110_2_i2c_resume,
	.driver = {
		.owner = THIS_MODULE,
		.name = "aw9110_2_dev",
	},
};

/*
 * module load/unload record keeping
 */

static int __init aw9110_2_dev_init(void)
{
	printk("aw9110_2_dev_init\n");
	return i2c_add_driver(&aw9110_2_i2c_driver);
}
module_init(aw9110_2_dev_init);

static void __exit aw9110_2_dev_exit(void)
{
	i2c_del_driver(&aw9110_2_i2c_driver);
}
module_exit(aw9110_2_dev_exit);


MODULE_AUTHOR("GoerTek");
MODULE_DESCRIPTION("aw9110_2 2c driver");
MODULE_LICENSE("GPL");
