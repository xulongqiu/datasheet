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
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/amlogic/aml_gpio_consumer.h>
#include <linux/amlogic/gpio-amlogic.h>

#define USE_IRQ 1
//#undef USE_IRQ

struct aw9110_1_i2c_dev {
	struct mutex read_mutex;
	struct i2c_client *client;
	struct miscdevice aw9110_misc_device;
	char * buf;
	int irq;
	unsigned int int_pin;
	irq_handler_t handler;
};

struct aw9110_1_i2c_dev *aw9110_1_dev;

static ssize_t aw9110_1_dev_read_local(int reg, char *buf)
{
	
	char reg_buf[2];
	int ret;
	mutex_lock(&aw9110_1_dev->read_mutex);
	reg_buf[0] = reg;
	ret = i2c_master_send(aw9110_1_dev->client, reg_buf, 1);

	ret = i2c_master_recv(aw9110_1_dev->client, buf, 1);
//	printk("%s %d buf = 0x%x\n",__func__,__LINE__, *buf);
	mutex_unlock(&aw9110_1_dev->read_mutex);
	
	if (ret != 1) 
	{
		dev_err(&aw9110_1_dev->client->dev,
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

static ssize_t aw9110_1_dev_write_local(int reg, char *buf) 
{
	int ret;
	char reg_buf[2];
	reg_buf[0] = reg;
	reg_buf[1] = *buf;

	mutex_lock(&aw9110_1_dev->read_mutex);
	ret = i2c_master_send(aw9110_1_dev->client, reg_buf, 2);
	mutex_unlock(&aw9110_1_dev->read_mutex);

	if(ret != 2) 
	{
		printk("fail to write the reg %d\n ", reg);
		ret = -EIO;
	}
	else
	{
		//printk("write the reg 0x%x  = 0x%x ok!\n ", reg, reg_buf[1]);
	}
	return ret;
}

void set_aw9110_ext_1_gpio_out(int out_index, int level)
{
	// set as gpio
	char reg, reg_value;
	unsigned char shift_bit;
//CTL
	reg = 0x11;
	aw9110_1_dev_read_local(reg, &reg_value);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | (1<<4);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);
	
	if(out_index > 3) {
		reg = 0x12;
		shift_bit = out_index - 4;
		aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x13;
		shift_bit = out_index;
		aw9110_1_dev_read_local(reg, &reg_value);
	}
	
//  printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | (1<<shift_bit);
//	printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);
//=set as output
	if(out_index > 3) {
		reg = 0x04;
		shift_bit = out_index - 4;
		aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x05;
		shift_bit = out_index;
		aw9110_1_dev_read_local(reg, &reg_value);
	}
	
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value & (~(1<<shift_bit));
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);
// set the gpio output level
	if(out_index > 3) {
		reg = 0x02;
		shift_bit = out_index - 4;
		aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x03;
		shift_bit = out_index;
		aw9110_1_dev_read_local(reg, &reg_value);
	}
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	if(level == 0)
		reg_value = reg_value & (~(1<<shift_bit));
	else
		reg_value = reg_value | (1<<shift_bit);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);
}
EXPORT_SYMBOL(set_aw9110_ext_1_gpio_out);

void set_aw9110_ext_1_gpio_in(int in_index)
{
// set as gpio
	char reg, reg_value;
	unsigned char shift_bit;

	if(in_index > 3) {
		reg = 0x12;
		shift_bit = in_index - 4;
		aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x13;
		shift_bit = in_index;
		aw9110_1_dev_read_local(reg, &reg_value);
	}
	
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	reg_value = reg_value | (1<<shift_bit);
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);
//=set as input 
	if(in_index > 3) {
		reg = 0x04;
		shift_bit = in_index - 4;
		aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x05;
		shift_bit = in_index;
		aw9110_1_dev_read_local(reg, &reg_value);
	}
	
	//printk("%s %d reg_value = 0x%x\n",__func__,__LINE__,reg_value);
	reg_value = reg_value | 1<<shift_bit;
	//printk("%s %d reg_value = 0x%x\n",__func__,__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);
}
EXPORT_SYMBOL(set_aw9110_ext_1_gpio_in);

int get_aw9110_ext_1_gpio_in_stat(int in_index)
{
	char reg, reg_value;
	unsigned char shift_bit;
    int ret = 0;

	//first set the gpio to input
	set_aw9110_ext_1_gpio_in(in_index);
	
	if(in_index > 3) {
		reg = 0x00;
		shift_bit = in_index - 4;
		ret = aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x01;
		shift_bit = in_index;
		ret = aw9110_1_dev_read_local(reg, &reg_value);
	}
    if(ret < 0)
        return ret;
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	return (reg_value >> shift_bit) & 0x01;
}
EXPORT_SYMBOL(get_aw9110_ext_1_gpio_in_stat);

int set_aw9110_ext_1_interrupt(int index, bool enable, irq_handler_t handler)
{
	char reg, reg_value;
	unsigned char shift_bit;

	if(aw9110_1_dev == NULL)
		return -1;
    
    //set irq handler
    if(aw9110_1_dev->handler == NULL && handler != NULL){
	    aw9110_1_dev->handler = handler;
    }
    //set as gpio input
	set_aw9110_ext_1_gpio_in(index);

    //enable or disable intterup
	if(index > 3) {
		reg = 0x06;
		shift_bit = index - 4;
		aw9110_1_dev_read_local(reg, &reg_value);
	} else {
		reg = 0x07;
		shift_bit = index;
		aw9110_1_dev_read_local(reg, &reg_value);
	}
	
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	if(enable){
		reg_value = reg_value & (~(1<<shift_bit));
	}else{
		reg_value = reg_value | (1<<shift_bit);
	}
	//printk("%d ---------reg_value = 0x%x\n",__LINE__,reg_value);
	aw9110_1_dev_write_local(reg, &reg_value);

	get_aw9110_ext_1_gpio_in_stat(0);
	get_aw9110_ext_1_gpio_in_stat(4);
	return 0;
}
EXPORT_SYMBOL(set_aw9110_ext_1_interrupt);

#ifdef USE_IRQ
static irqreturn_t irq_handler(int irq, void* data)
{
    if(aw9110_1_dev && aw9110_1_dev->handler)
	    return aw9110_1_dev->handler(irq, data);
		
    return IRQ_HANDLED;
}
#endif

static int aw9110_1_dev_open(struct inode *inode, struct file *filp)
{
	int ret = 0;

	struct aw9110_1_i2c_dev *aw9110_1_dev = container_of(filp->private_data,
							   struct aw9110_1_i2c_dev,
							   aw9110_misc_device);
	filp->private_data = aw9110_1_dev;
	dev_info(&aw9110_1_dev->client->dev,
		 "device node major=%d, minor=%d\n", imajor(inode), iminor(inode));

	return ret;
}

static long aw9110_1_dev_unlocked_ioctl(struct file *filp,
					 unsigned int cmd, unsigned long arg)
{
	struct aw9110_1_i2c_dev *aw9110_1_dev = filp->private_data;

	switch (cmd) {
	case 1: 
		set_aw9110_ext_1_gpio_out(1, 1);
		break;
	case 2: 
		set_aw9110_ext_1_gpio_out(2, 1);
		break;
	case 3: 
		set_aw9110_ext_1_gpio_out(3, 1);
		break;
	case 4: 
		set_aw9110_ext_1_gpio_out(4, 1);
		break;
	case 5: 
		set_aw9110_ext_1_gpio_out(5, 1);
		break;
	case 6: 
		set_aw9110_ext_1_gpio_out(6, 1);
		break;
	case 7: 
		set_aw9110_ext_1_gpio_out(7, 1);
		break;
	case 8: 
		set_aw9110_ext_1_gpio_out(8, 1);
		break;
	default:
		dev_err(&aw9110_1_dev->client->dev,
			"%s, unknown cmd (%x, %lx)\n", __func__, cmd, arg);
		return 0;
	}

	return 0;
}

static ssize_t aw9110_1_dev_read(struct file *filp, char __user *buf,
				  size_t count, loff_t *offset)
{
	struct aw9110_1_i2c_dev *aw9110_1_dev = filp->private_data;
	int total, len, ret;

	total = 0;
	len = 0;

	if (count > 128)
	{
		dev_err(&aw9110_1_dev->client->dev, "read out of memory %d\n", count);
		count = 128;
	}
	
	mutex_lock(&aw9110_1_dev->read_mutex);
	ret = i2c_master_recv(aw9110_1_dev->client, aw9110_1_dev->buf, count);
	mutex_unlock(&aw9110_1_dev->read_mutex);
	
	if (ret != count) 
	{
			dev_err(&aw9110_1_dev->client->dev,
				"failed to read %d byte return %d\n", count, ret);
			ret = -EIO;

			return ret;
	} /* if */
	else
	{
		dev_info(&aw9110_1_dev->client->dev,
		 	"read %d byte --> %2x,%2x,%2x,%2x,%2x,%2x,%2x,%2x,%2x,%2x\n", 
		 	count, *(aw9110_1_dev->buf), *(aw9110_1_dev->buf+1),*(aw9110_1_dev->buf+2),*(aw9110_1_dev->buf+3),*(aw9110_1_dev->buf+4),*(aw9110_1_dev->buf+5),
		 	*(aw9110_1_dev->buf+6),*(aw9110_1_dev->buf+7),*(aw9110_1_dev->buf+8),*(aw9110_1_dev->buf+9));
	}

	if (copy_to_user(buf, aw9110_1_dev->buf, count)) {
		dev_err(&aw9110_1_dev->client->dev,
			"failed to copy to user space, count = %d\n", count);
		count = -EFAULT;
	}

	return count;
}

static ssize_t aw9110_1_dev_write(struct file *filp, const char __user *buf,
				   size_t count, loff_t *offset)
{
	struct aw9110_1_i2c_dev *aw9110_1_dev = filp->private_data;
	int ret;

	if (count > 128) {
		dev_err(&aw9110_1_dev->client->dev, "write out of memory %d\n", count);
		return -ENOMEM;
	}

	if (copy_from_user(aw9110_1_dev->buf, buf, count)) {
		dev_err(&aw9110_1_dev->client->dev,
			"failed to copy from user space\n");
		return -EFAULT;
	}


	mutex_lock(&aw9110_1_dev->read_mutex);
	ret = i2c_master_send(aw9110_1_dev->client, aw9110_1_dev->buf, count);
	mutex_unlock(&aw9110_1_dev->read_mutex);

	if(ret != count) 
	{
			dev_err(&aw9110_1_dev->client->dev,
				"failed to %d byte [%x:%x] write %d\n",count, *(aw9110_1_dev->buf), *(aw9110_1_dev->buf+1), ret);
			ret = -EIO;
	}
	else
	{
		dev_info(&aw9110_1_dev->client->dev,
		 	"write %d byte ok -->  %2x,%2x\n",
			count, *(aw9110_1_dev->buf), *(aw9110_1_dev->buf+1));
	}

	return ret;
}

void aw9110_1_init()
{
	//just for test
#if 0
		printk("index = 0");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(0, 0);
	printk("index = 1");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(1, 1);
	printk("index = 2");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(2, 1);
	printk("index = 3");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(3, 0);
	printk("index = 4");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(4, 1);
	printk("index = 5");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(5, 1);
	printk("index = 6");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(6, 1);
	printk("index = 7");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(7, 1);
	printk("index = 8");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(8, 1);
	printk("index = 9");
	printk("**************************************");
	set_aw9110_ext_1_gpio_out(9, 0);
//============
#endif

#if 1
	printk("index = 0");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(0);
	printk("index = 1");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(1);
	printk("index = 2");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(2);
	printk("index = 3");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(3);
	printk("index = 4");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(4);
	printk("index = 5");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(5);
	printk("index = 6");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(6);
	printk("index = 7");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(7);
	printk("index = 8");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(8);
	printk("index = 9");
	printk("**************************************");
	set_aw9110_ext_1_gpio_in(9);
#endif
}


static const struct file_operations aw9110_1_dev_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.read = aw9110_1_dev_read,
	.write = aw9110_1_dev_write,
	.open = aw9110_1_dev_open,
	.unlocked_ioctl = aw9110_1_dev_unlocked_ioctl
};

static int aw9110_1_i2c_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	int ret;
	int irq_num = 0;
	unsigned int gpio_int = 0;
	const char *str = NULL;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "need I2C_FUNC_I2C\n");
		return -ENODEV;
	}
#ifdef USE_IRQ
    ret = of_property_read_u32(client->dev.of_node, "irq_num", &irq_num);

    if (ret) {
        printk(KERN_INFO "eric.xu:Failed to get aw9110 irq number from dts.\n");
        return -ENODEV;
    }
    /*gpio_int_pin*/
    ret = of_property_read_string(client->dev.of_node, "gpio_int_pin", &str);

    if (ret) {
        printk(KERN_WARNING "not get gpio_int_pin\n");
        return  -ENODEV;
    } else {
        gpio_int = amlogic_gpio_name_map_num(str);
    }

    printk("eric.xu:extern_gpio_1,gpio_int = %d\n", gpio_int);

    if (!gpio_is_valid(gpio_int)) {
        pr_err("eric.xu:%s: invalid GPIO pins, int =%d\n", client->dev.of_node->full_name, gpio_int);
        return -ENODEV;
    }

    ret = amlogic_gpio_request(gpio_int, "aw9110_12c");

    if (ret) {
        printk("eric.xu:gpio_request int_pin  ret = %d\n", ret);

        if (ret == -EINVAL) {
            ret = -EPROBE_DEFER;
        }

        goto err_request_int;
    }

    amlogic_gpio_direction_input(gpio_int, "aw9110_12c");
    //amlogic_set_pull_up_down(dev->int_pin, 1, DRV_NAME);
    amlogic_gpio_to_irq(gpio_int, "aw9110_12c",
                        AML_GPIO_IRQ(irq_num, FILTER_NUM7, GPIO_IRQ_LOW));
#endif

	aw9110_1_dev = kzalloc(sizeof(*aw9110_1_dev), GFP_KERNEL);
	if (aw9110_1_dev == NULL) {
		dev_err(&client->dev,
			"failed to allocate memory for module data\n");
		ret = -ENOMEM;
		goto err_exit;
	}
	aw9110_1_dev->buf = kzalloc(128, GFP_KERNEL);
	if(aw9110_1_dev->buf == NULL)
	{
		dev_err(&client->dev, "failed to allocate memory for rw buffer\n");
		ret = -ENOMEM;
		goto err_exit1;
	}
	aw9110_1_dev->client = client;

	mutex_init(&aw9110_1_dev->read_mutex);
	aw9110_1_dev->aw9110_misc_device.minor = MISC_DYNAMIC_MINOR;
	aw9110_1_dev->aw9110_misc_device.name = "aw9110_12c";
	aw9110_1_dev->aw9110_misc_device.fops = &aw9110_1_dev_fops;

	ret = misc_register(&aw9110_1_dev->aw9110_misc_device);
	if (ret) {
		printk("misc_register failed\n");
		goto err_misc_register;
	}
#ifdef USE_IRQ
	aw9110_1_dev->irq = irq_num;
	aw9110_1_dev->int_pin = gpio_int;
	if (request_irq(aw9110_1_dev->irq + INT_GPIO_0, irq_handler, IRQF_DISABLED, "irq_aw9110", aw9110_1_dev)) {
        printk(KERN_INFO "eric.xu: Failed to request irq.\n");
        ret = -EINVAL;
		  goto err_misc_register;
   }
#endif
	aw9110_1_init();
	dev_info(&client->dev, "%s, saving address %d\n",__func__, client->addr);

	i2c_set_clientdata(client, aw9110_1_dev);
	dev_info(&client->dev,
		 "%s, probing aw9110_1 i2c driver exited successfully\n",
		 __func__);
	return 0;
err_misc_register:
	mutex_destroy(&aw9110_1_dev->read_mutex);
err_exit1:
	kfree(aw9110_1_dev->buf);
err_exit:
	kfree(aw9110_1_dev);
err_request_int:
#ifdef USE_IRQ
    gpio_free(gpio_int);
#endif
	return ret;
}

static int aw9110_1_i2c_remove(struct i2c_client *client)
{
	struct aw9110_1_i2c_dev *aw9110_1_dev;

	aw9110_1_dev = i2c_get_clientdata(client);
	mutex_destroy(&aw9110_1_dev->read_mutex);

	kfree(aw9110_1_dev);

	return 0;
}

#ifdef CONFIG_PM
static int aw9110_1_i2c_suspend(struct i2c_client* client, pm_message_t mesg)
{
    printk(KERN_INFO "aw9110_1_i2c_suspend..\n");
    return 0;
}

static int aw9110_1_i2c_resume(struct i2c_client* client)
{
	aw9110_1_init();
	printk(KERN_INFO "aw9110_1_i2c_resume..\n");
	return 0;
}


#else
#define aw9110_1_i2c_suspend NULL
#define aw9110_1_i2c_resume NULL
#endif /* CONFIG_PM */

static const struct i2c_device_id aw9110_1_i2c_id[] = {
	{"aw9110_ext_1", 0},
	{}
};

static struct i2c_driver aw9110_1_i2c_driver = {
	.id_table = aw9110_1_i2c_id,
	.probe = aw9110_1_i2c_probe,
	.remove = aw9110_1_i2c_remove,
   .suspend = aw9110_1_i2c_suspend,
   .resume = aw9110_1_i2c_resume,
	.driver = {
		.owner = THIS_MODULE,
		.name = "aw9110_1_dev",
	},
};


/*
 * module load/unload record keeping
 */

static int __init aw9110_1_dev_init(void)
{
	printk("aw9110_1_dev_init\n");
	return i2c_add_driver(&aw9110_1_i2c_driver);
}
module_init(aw9110_1_dev_init);

static void __exit aw9110_1_dev_exit(void)
{
	i2c_del_driver(&aw9110_1_i2c_driver);
}
module_exit(aw9110_1_dev_exit);


MODULE_AUTHOR("GoerTek");
MODULE_DESCRIPTION("Aw9110_1 2c driver");
MODULE_LICENSE("GPL");
