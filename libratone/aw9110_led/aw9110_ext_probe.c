/*******************************************************************
 *
 *  Copyright C 2010 by libratone, Inc. All Rights Reserved.
 *
 *  Description:
 *
 *  Author: libratone Software
 *
 *******************************************************************/
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/regmap.h>
#include <linux/pinctrl/consumer.h>
#include <mach/am_regs.h>
#include <linux/delay.h>
#include <mach/gpio.h>
#include "aw9110_ext_probe.h"

static int delta_ext_gpio_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct device_node* ext_gpio_node = pdev->dev.of_node;
    struct device_node* child;
	struct i2c_client *client;
	struct i2c_adapter *adapter;
	const char* str;

	aw9110_dev_info_t *aw9110_dev_info;
	aw9110_dev_info = kzalloc(sizeof(aw9110_dev_info_t), GFP_KERNEL);

    printk("%s %d\n",__func__,__LINE__);
    for_each_child_of_node(ext_gpio_node, child) {
		struct i2c_board_info board_info;
        memset(aw9110_dev_info, 0, sizeof(aw9110_dev_info_t));

		ret = of_property_read_string(child, "dev_name", &aw9110_dev_info->name);
		if (ret) {
			printk("no of property dev_name !\n");
			goto exit;
		}
		ret = of_property_read_string(child, "status", &aw9110_dev_info->status);
		if (ret) {
			printk("no of property status %s!\n");
			goto exit;
		}
		if (strcmp(aw9110_dev_info->status, "okay") && strcmp(aw9110_dev_info->status, "ok")){
			printk("node %s disable\n", aw9110_dev_info->status);
			ret = -ENODEV;
			goto exit;
		}

		ret = of_property_read_u32(child,"i2c_addr", &aw9110_dev_info->i2c_addr);
		if(ret){
			printk("%s fail to get i2c_addr\n", __func__);
			goto exit;
		}
#if 0
		ret = of_property_read_u32(child,"id_reg", &audio_codec_dev->id_reg);
		if(ret){
			printk("%s fail to get id_reg\n", __func__);
			goto exit;
		}

		ret = of_property_read_u32(child,"id_val", &audio_codec_dev->id_val);
		if(ret){
			printk("%s fail to get id_val\n", __func__);
			goto exit;
		}
#endif
		ret = of_property_read_string(child, "i2c_bus", &str);
		if(ret){
			printk("%s fail to get i2c_bus\n", __func__);
			goto exit;
		}
	
		if (!strncmp(str, "i2c_bus_ao", 10))
			aw9110_dev_info->i2c_bus_type = AML_I2C_BUS_AO;
		else if (!strncmp(str, "i2c_bus_a", 9))
			aw9110_dev_info->i2c_bus_type = AML_I2C_BUS_A;
		else if (!strncmp(str, "i2c_bus_b", 9))
			aw9110_dev_info->i2c_bus_type = AML_I2C_BUS_B;
		else if (!strncmp(str, "i2c_bus_c", 9))
			aw9110_dev_info->i2c_bus_type = AML_I2C_BUS_C;
		else if (!strncmp(str, "i2c_bus_d", 9))
			aw9110_dev_info->i2c_bus_type = AML_I2C_BUS_D;
		else
			printk("ERR, unsupported i2c bus addr: %s \n", str);
	
		adapter = i2c_get_adapter(aw9110_dev_info->i2c_bus_type);
		if (!adapter){
			ret = -ENODEV;
			goto err2;
		}
	
		strncpy(board_info.type, aw9110_dev_info->name, I2C_NAME_SIZE);
		printk("board_info.type = %s\n",&(board_info.type));
//	strncpy(board_info.type, "codec_i2c", I2C_NAME_SIZE);
		board_info.addr = aw9110_dev_info->i2c_addr;
		board_info.of_node = child;
		client = i2c_new_device(adapter, &board_info);
		if (!client) {
			/* I2C device registration failed, continue with the next */
			printk("Unable to add I2C device for 0x%x\n",
				   board_info.addr);
			ret = -ENODEV;
			goto err1;
		}
		printk(" -----add a new i2c device %s\n",aw9110_dev_info->name);
	}
	return 0;
err1:
	i2c_unregister_device(client);
err2:
	i2c_put_adapter(adapter);
exit:
	kfree(aw9110_dev_info);
	return ret;
}

static int delta_ext_gpio_remove(struct platform_device *pdev)
{
    return 0;
}

static const struct of_device_id delta_ext_gpio_probe_dt_match[]={
    {
        .compatible = "aw9110-ext-gpio",
    },
    {},
};

static  struct platform_driver delta_ext_probe_driver = {
    .probe      = delta_ext_gpio_probe,
    .remove     = delta_ext_gpio_remove,
    .driver     = {
        .name   = "delta_ext_gpio_probe",
        .owner  = THIS_MODULE,
        .of_match_table = delta_ext_gpio_probe_dt_match,
    },
};

static int __init delta_ext_gpio_init(void)
{
    int ret;

    ret = platform_driver_register(&delta_ext_probe_driver);
    if (ret){
        printk(KERN_ERR"delta_ext_probre_driver register failed\n");
        return ret;
    }

    return ret;
}

static void __exit delta_ext_gpio_exit(void)
{
    platform_driver_unregister(&delta_ext_probe_driver);
}

module_init(delta_ext_gpio_init);
module_exit(delta_ext_gpio_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ext gpio prober driver");

