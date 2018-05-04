/*
 * leds-aw9120.c   aw9120 led module
 *
 * Copyright (c) 2017 AWINIC Technology CO., LTD
 *
 *  Author: Nick Li <liweilei@awinic.com.cn>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/firmware.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/debugfs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/leds.h>
#include <linux/amlogic/aml_gpio_consumer.h>
#include <linux/amlogic/gpio-amlogic.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include "aw9120.h"
/******************************************************
 *
 * Marco
 *
 ******************************************************/
#define AW9120_CMD_MAGIC 'k'
#define AW9120_CMD_RESET _IO(AW9120_CMD_MAGIC, 0x80)
#define AW9120_CMD_PWR _IOW(AW9120_CMD_MAGIC, 0x81, int)
#define AW9120_CMD_ALL_BLINK    _IOW(AW9120_CMD_MAGIC, 0x82, int)
#define AW9120_CMD_LIGHT    _IOW(AW9120_CMD_MAGIC, 0x83, uint8_t*)
#define MAX_BUFFER_SIZE 28

#define AW9120_I2C_NAME "aw9120_led"

#define AW9120_VERSION "v1.0.0"

#define I2C_err_cnt_MAX  255

#define AW_I2C_RETRIES 1
#define AW_I2C_RETRY_DELAY 5
#define AW_READ_CHIPID_RETRIES 5
#define AW_READ_CHIPID_RETRY_DELAY 5

#define REG_RSTR    0x00
#define REG_GCR     0x01

#define REG_LER1    0x50
#define REG_LER2    0x51
#define REG_LCR     0x52
#define REG_PMR     0x53
#define REG_RMR     0x54
#define REG_CTRS1   0x55
#define REG_CTRS2   0x56
#define REG_IMAX1   0x57
#define REG_IMAX2   0x58
#define REG_IMAX3   0x59
#define REG_IMAX4   0x5a
#define REG_IMAX5   0x5b
#define REG_TIER    0x5c
#define REG_INTVEC  0x5d
#define REG_LISR2   0x5e
#define REG_SADDR   0x5f

#define REG_PCR     0x60
#define REG_CMDR    0x61
#define REG_RA      0x62
#define REG_RB      0x63
#define REG_RC      0x64
#define REG_RD      0x65
#define REG_R1      0x66
#define REG_R2      0x67
#define REG_R3      0x68
#define REG_R4      0x69
#define REG_R5      0x6a
#define REG_R6      0x6b
#define REG_R7      0x6c
#define REG_R8      0x6d
#define REG_GRPMSK1 0x6e
#define REG_GRPMSK2 0x6f

#define REG_TCR     0x70
#define REG_TAR     0x71
#define REG_TDR     0x72
#define REG_TDATA   0x73
#define REG_TANA    0x74
#define REG_TKST    0x75
#define REG_FEXT    0x76
#define REG_WP      0x7d
#define REG_WADDR   0x7e
#define REG_WDATA   0x7f

/* aw9120 register read/write access*/
#define REG_NONE_ACCESS                 0
#define REG_RD_ACCESS                   1 << 0
#define REG_WR_ACCESS                   1 << 1
#define AW9120_REG_MAX                  0xFF
const unsigned char aw9120_reg_access[AW9120_REG_MAX] = {
    [REG_RSTR   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_GCR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_LER1   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_LER2   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_LCR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_PMR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_RMR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_CTRS1  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_CTRS2  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_IMAX1  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_IMAX2  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_IMAX3  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_IMAX4  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_IMAX5  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_TIER   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_INTVEC ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_LISR2  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_SADDR  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_PCR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_CMDR   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_RA     ] = REG_RD_ACCESS,
    [REG_RB     ] = REG_RD_ACCESS,
    [REG_RC     ] = REG_RD_ACCESS,
    [REG_RD     ] = REG_RD_ACCESS,
    [REG_R1     ] = REG_RD_ACCESS,
    [REG_R2     ] = REG_RD_ACCESS,
    [REG_R3     ] = REG_RD_ACCESS,
    [REG_R4     ] = REG_RD_ACCESS,
    [REG_R5     ] = REG_RD_ACCESS,
    [REG_R6     ] = REG_RD_ACCESS,
    [REG_R7     ] = REG_RD_ACCESS,
    [REG_R8     ] = REG_RD_ACCESS,
    [REG_GRPMSK1] = REG_RD_ACCESS,
    [REG_GRPMSK2] = REG_RD_ACCESS,
    [REG_TCR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_TAR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_TDR    ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_TDATA  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_TANA   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_TKST   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_FEXT   ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_WP     ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_WADDR  ] = REG_RD_ACCESS | REG_WR_ACCESS,
    [REG_WDATA  ] = REG_RD_ACCESS | REG_WR_ACCESS
};


/******************************************************
 *
 * aw9120 led parameter
 *
 ******************************************************/
/* The definition of each time described as shown in figure.
 *        /-----------\
 *       /      |      \
 *      /|      |      |\
 *     / |      |      | \-----------
 *       |hold_time_ms |      |
 *       |             |      |
 * rise_time_ms  fall_time_ms |
 *                       off_time_ms
 */
#define ROM_CODE_MAX 255

/*
 * rise_time_ms = 1500
 * hold_time_ms = 500
 * fall_time_ms = 1500
 * off_time_ms = 1500
 */
static int led_code_len = 7;
static int led_code[ROM_CODE_MAX] = {
    0xbf00, 0x9f05, 0xfffa, 0x3c7d/*waiti pre = 1, t = 0x7d*/, 0xdffa, 0x3cbb/*waiti pre = 1, t = bb*/, 0x2/*jump to address 0x02*/,
};

static int blink_on_index_len = 15;
static int blink_on_index_code[ROM_CODE_MAX] = {
    0x9f05 , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe00, 0xfefa, 0x3c7d, 0xdefa, 0x3cbb, 0x9,
};

static int aw9120_hw_reset(struct aw9120* aw9120)
{
    pr_info("%s enter\n", __func__);

    if (aw9120 && gpio_is_valid(aw9120->reset_gpio)) {
        gpio_direction_output(aw9120->reset_gpio, 0);
        msleep(1);
        gpio_direction_output(aw9120->reset_gpio, 1);
        msleep(20);
    } else {
        dev_err(aw9120->dev, "%s:  failed\n", __func__);
    }

    return 0;
}

/******************************************************
 *
 * aw9120 i2c write/read
 *
 ******************************************************/
static int i2c_write(struct aw9120* aw9120,
                     unsigned char addr, unsigned int reg_data)
{
    int ret;
    unsigned char wbuf[512] = {0};

    struct i2c_msg msgs[] = {
        {
            .addr = aw9120->i2c->addr,
            .flags = 0,
            .len = 3,
            .buf = wbuf,
        },
    };

    wbuf[0] = addr;
    wbuf[1] = (unsigned char)(reg_data >> 8);
    wbuf[2] = (unsigned char)(reg_data & 0x00ff);

    ret = i2c_transfer(aw9120->i2c->adapter, msgs, 1);

    if (ret < 0) {
        pr_err("%s: i2c write error: %d\n", __func__, ret);
    }

    return ret;
}

static int i2c_read(struct aw9120* aw9120,
                    unsigned char addr, unsigned int* reg_data)
{
    int ret;
    unsigned char rbuf[512] = {0};
    unsigned int get_data;

    struct i2c_msg msgs[] = {
        {
            .addr = aw9120->i2c->addr,
            .flags = 0,
            .len = 1,
            .buf = &addr,
        },
        {
            .addr = aw9120->i2c->addr,
            .flags = I2C_M_RD,
            .len = 2,
            .buf = rbuf,
        },
    };

    ret = i2c_transfer(aw9120->i2c->adapter, msgs, 2);

    if (ret < 0) {
        pr_err("%s: i2c read error: %d\n", __func__, ret);
        return ret;
    }

    get_data = (unsigned int)(rbuf[0] << 8);
    get_data |= (unsigned int)(rbuf[1]);

    *reg_data = get_data;

    return ret;
}

static int aw9120_i2c_write(struct aw9120* aw9120,
                            unsigned char reg_addr, unsigned int reg_data)
{
    int ret = -1;
    unsigned char cnt = 0;
    
    if(++aw9120->err_cnt > I2C_err_cnt_MAX){
        return -1;
    }

    while (cnt < AW_I2C_RETRIES) {
        ret = i2c_write(aw9120, reg_addr, reg_data);
        if (ret < 0) {
            aw9120->err_cnt++;
            if(aw9120->err_cnt == I2C_err_cnt_MAX){
                dev_err(&aw9120->i2c->dev, "request write error many times(%d)\n", aw9120->err_cnt);
            }
            pr_err("%s: i2c_write cnt=%d error=%d\n", __func__, cnt, ret);
        } else {
            aw9120->err_cnt = 0;
            break;
        }

        cnt ++;
        msleep(AW_I2C_RETRY_DELAY);
    }

    return ret;
}

static int aw9120_i2c_read(struct aw9120* aw9120,
                           unsigned char reg_addr, unsigned int* reg_data)
{
    int ret = -1;
    unsigned char cnt = 0;
        
    if(++aw9120->err_cnt > I2C_err_cnt_MAX){
        return -1;
    }

    while (cnt < AW_I2C_RETRIES) {
        ret = i2c_read(aw9120, reg_addr, reg_data);

        if (ret < 0) {
            aw9120->err_cnt++;
            if(aw9120->err_cnt == I2C_err_cnt_MAX){
                dev_err(&aw9120->i2c->dev, "request read error many times(%d)\n", aw9120->err_cnt);
            }
            pr_err("%s: i2c_read cnt=%d error=%d\n", __func__, cnt, ret);
        } else {
            aw9120->err_cnt = 0;
            break;
        }

        cnt++;
        msleep(AW_I2C_RETRY_DELAY);
    }

    return ret;
}

static int aw9120_led_light(struct aw9120* aw9120, uint8_t index, uint8_t level)
{
    int ret = 0;

    if(index > 19){
        return -1;
    }
    if(index > 11){
        ret = aw9120_i2c_write(aw9120, REG_CTRS1, 0);    // CTRS1-LED1~LED12: i2c Control
        if(ret < 0){
            return ret;
        }
        ret = aw9120_i2c_write(aw9120, REG_CTRS2, 1 <<(index - 12));    // CTRS2-LED13~LED20: i2c Control
        if(ret < 0){
            return ret;
        }
    }else{
        ret = aw9120_i2c_write(aw9120, REG_CTRS1, 1 << index);    // CTRS1-LED1~LED12: i2c Control
        if(ret < 0){
            return ret;
        }
        ret = aw9120_i2c_write(aw9120, REG_CTRS2, 0);    // CTRS2-LED13~LED20: i2c Control 
        if(ret < 0){
            return ret;
        }
    }
    // LED Control
    return aw9120_i2c_write(aw9120, REG_CMDR,
                    0xBF00 | level);      // CMDR-LED1~LED20 PWM=0xFF
}

static int aw9120_dev_init(struct aw9120* aw9120)
{
    uint16_t reg_val;
    uint16_t imax = 0x7777;

    aw9120_hw_reset(aw9120);
    aw9120->err_cnt = 0; 
    //Enable LED Module
    aw9120_i2c_read(aw9120, REG_GCR, &reg_val);
    reg_val = 0xFFFF;
    aw9120_i2c_write(aw9120, REG_GCR, reg_val);     // GCR-Disable LED Module

    //LED Config
    aw9120_i2c_write(aw9120, REG_IMAX1, imax);      // IMAX1-LED1~LED4 Current
    aw9120_i2c_write(aw9120, REG_IMAX2, imax);      // IMAX2-LED5~LED8 Current
    aw9120_i2c_write(aw9120, REG_IMAX3, imax);      // IMAX3-LED9~LED12 Current
    aw9120_i2c_write(aw9120, REG_IMAX4, imax);      // IMAX4-LED13~LED16 Current
    aw9120_i2c_write(aw9120, REG_IMAX5, imax);      // IMAX5-LED17~LED20 Current
    aw9120_i2c_write(aw9120, REG_LER1, 0x0FFF);     // LER1-LED1~LED12 Enable
    aw9120_i2c_write(aw9120, REG_LER2, 0x00FF);     // LER2-LED13~LED20 Enable
    aw9120_i2c_write(aw9120, REG_CTRS1, 0x0FFF);    // CTRS1-LED1~LED12: i2c Control
    aw9120_i2c_write(aw9120, REG_CTRS2, 0x00FF);    // CTRS2-LED13~LED20: i2c Control

    // LED Control, level 0
    aw9120_i2c_write(aw9120, REG_CMDR, 0xBF00);      // CMDR-LED1~LED20 PWM=0xFF
    
    return 0;
}

#if LED_UI_DRIVER
#define SPIN_LEV_1  1
#define SPIN_LEV_2  4
#define SPIN_LEV_3  8
#define SPIN_LEV_4  16
#define SPIN_LEV_5  64
#define SPIN_LEV_6  255

static const unsigned char led_circle_table[12][12] = {
    {SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, 0, 0},
    {SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, 0, 0, SPIN_LEV_6},
    {SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5},
    {SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4},
    {SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3},
    {SPIN_LEV_1, 0, 0, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2},
    {0, 0, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1},
    {0, 0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0},
    {0, 0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0},
    {0, 0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0},
    {0, 0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0},
    {0, SPIN_LEV_6, SPIN_LEV_5, SPIN_LEV_4, SPIN_LEV_3, SPIN_LEV_2, SPIN_LEV_1, 0, 0, 0, 0, 0},
};

static void update_work_func(struct work_struct* work)
{
    struct aw9120* dev = container_of(work, struct aw9120, work_update);
    static unsigned char index = 0;
    int i = 0;

    if (!(dev->setup)) {
        aw9120_dev_init(dev);
        dev->setup = true;
    }
    
    for(i=0; i< sizeof(led_circle_table[index])/sizeof(led_circle_table[index][0]); i++){
        if(aw9120_led_light(dev, i, led_circle_table[index][i]) < 0){
            return;
        }
    }
    index = (++index) % 12;
}

static void aw9120_timer_sr(unsigned long data)
{
    struct aw9120* dev = (struct aw9120*)data;
    schedule_work(&(dev->work_update));
    mod_timer(&dev->timer, jiffies + msecs_to_jiffies(100));
}

#endif
#if 0
static int aw9120_i2c_write_bits(struct aw9120* aw9120,
                                 unsigned char reg_addr, unsigned int mask, unsigned int reg_data)
{
    unsigned int reg_val;

    aw9120_i2c_read(aw9120, reg_addr, &reg_val);
    reg_val &= mask;
    reg_val |= reg_data;
    aw9120_i2c_write(aw9120, reg_addr, reg_val);

    return 0;
}
#endif

/*****************************************************
 *
 * device tree
 *
 *****************************************************/
static int aw9120_parse_dt(struct device* dev, struct aw9120* aw9120,
                           struct device_node* np, enum of_gpio_flags* pflags/*useless parameter*/)
{
    const __be32* addr;         //need init
    unsigned int gpio;          //need init
    const char* str;            //need init
    int len = 0;                    //need init
    int ret = 0;

    addr = of_get_property(np, "reg", &len);
    printk("addr=0x%02x\n", be32_to_cpup(addr));
    printk("node name = %s\n", np->full_name);


    ret = of_property_read_string(np, "gpio_sdb_pin", &str);

    if (ret) {
        printk(KERN_WARNING "not get gpio_led_sdb\n");
        return -ENODEV;
    } else {
        gpio = amlogic_gpio_name_map_num(str);
    }

    aw9120->reset_gpio = gpio;
    return 0;
}


/*****************************************************
 *
 * check chip id
 *
 *****************************************************/
static int aw9120_read_chipid(struct aw9120* aw9120)
{
    int ret = -1;
    unsigned char cnt = 0;
    unsigned int reg_val = 0;

    while (cnt < AW_READ_CHIPID_RETRIES) {
        ret = aw9120_i2c_read(aw9120, REG_RSTR, &reg_val);

        if (ret < 0) {
            dev_err(aw9120->dev,
                    "%s: failed to read register AW9120_REG_ID: %d\n",
                    __func__, ret);
            return -EIO;
        }

        switch (reg_val) {
        case 0xb223:
            pr_info("%s aw9120 detected\n", __func__);
            aw9120->chipid = AW9120_ID;
            return 0;

        default:
            pr_info("%s unsupported device revision (0x%x)\n",
                    __func__, reg_val);
            break;
        }

        cnt ++;

        msleep(AW_READ_CHIPID_RETRY_DELAY);
    }

    return -EINVAL;

}

#if 0

/******************************************************
 *
 * sys group attribute: reg
 *
 ******************************************************/
static ssize_t aw9120_reg_store(struct device* dev, struct device_attribute* attr,
                                const char* buf, size_t count)
{
    struct miscdevice cdev = dev_get_drvdata(dev);
    struct aw9120* aw9120 = container_of(cdev, struct aw9120, cdev);

    unsigned int databuf[2] = {0, 0};

    if (2 == sscanf(buf, "%x %x", &databuf[0], &databuf[1])) {
        aw9120_i2c_write(aw9120, databuf[0], databuf[1]);
    }

    return count;
}

static ssize_t aw9120_reg_show(struct device* dev, struct device_attribute* attr,
                               char* buf)
{
    struct miscdevice cdev = dev_get_drvdata(dev);
    struct aw9120* aw9120 = container_of(cdev, struct aw9120, cdev);
    ssize_t len = 0;
    unsigned char i = 0;
    unsigned int reg_val = 0;

    for (i = 0; i < AW9120_REG_MAX; i ++) {
        if (!(aw9120_reg_access[i]&REG_RD_ACCESS)) {
            continue;
        }

        aw9120_i2c_read(aw9120, i, &reg_val);
        len += snprintf(buf + len, PAGE_SIZE - len, "reg:0x%02x=0x%04x \n", i, reg_val);
    }

    return len;
}

static int aw9120_hw_off(struct aw9120* aw9120)
{
    pr_info("%s enter\n", __func__);

    if (aw9120 && gpio_is_valid(aw9120->reset_gpio)) {
        gpio_set_value_cansleep(aw9120->reset_gpio, 0);
        msleep(1);
    } else {
        dev_err(aw9120->dev, "%s:  failed\n", __func__);
    }

    return 0;
}

static ssize_t aw9120_hwen_store(struct device* dev, struct device_attribute* attr,
                                 const char* buf, size_t count)
{
    struct miscdevice cdev = dev_get_drvdata(dev);
    struct aw9120* aw9120 = container_of(cdev, struct aw9120, cdev);

    unsigned int databuf[1] = {0};

    if (1 == sscanf(buf, "%x", &databuf[0])) {
        if (1 == databuf[0]) {
            aw9120_hw_reset(aw9120);
        } else {
            aw9120_hw_off(aw9120);
        }
    }

    return count;
}

static ssize_t aw9120_hwen_show(struct device* dev, struct device_attribute* attr,
                                char* buf)
{
    struct miscdevice cdev = dev_get_drvdata(dev);
    struct aw9120* aw9120 = container_of(cdev, struct aw9120, cdev);
    ssize_t len = 0;
    len += snprintf(buf + len, PAGE_SIZE - len, "hwen=%d\n",
                    gpio_get_value(aw9120->reset_gpio));

    return len;
}

static ssize_t aw9120_ram_store(struct device* dev, struct device_attribute* attr,
                                const char* buf, size_t count)
{
    struct miscdevice cdev = dev_get_drvdata(dev);
    struct aw9120* aw9120 = container_of(cdev, struct aw9120, cdev);

    unsigned int databuf[1] = {0};

    if (1 == sscanf(buf, "%x", &databuf[0])) {
        if (1 == databuf[0]) {
            aw9120_ram_update(aw9120);
        }
    }

    return count;
}

static ssize_t aw9120_ram_show(struct device* dev, struct device_attribute* attr,
                               char* buf)
{
    ssize_t len = 0;

    return len;
}

static ssize_t aw9120_blink_store(struct device* dev, struct device_attribute* attr,
                                  const char* buf, size_t len)
{
    unsigned int databuf[1];
    struct miscdevice cdev = dev_get_drvdata(dev);
    struct aw9120* aw9120 = container_of(cdev, struct aw9120, cdev);

    sscanf(buf, "%d", &databuf[0]);
    aw9120_led_blink(aw9120, databuf[0]);

    return len;
}

static ssize_t aw9120_blink_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    ssize_t len = 0;
    len += snprintf(buf + len, PAGE_SIZE - len, "aw9120_blink()\n");
    len += snprintf(buf + len, PAGE_SIZE - len, "echo 0 > blink\n");
    len += snprintf(buf + len, PAGE_SIZE - len, "echo 1 > blink\n");

    return len;
}


static DEVICE_ATTR(reg, S_IWUSR | S_IRUGO, aw9120_reg_show, aw9120_reg_store);
static DEVICE_ATTR(hwen, S_IWUSR | S_IRUGO, aw9120_hwen_show, aw9120_hwen_store);
static DEVICE_ATTR(ram, S_IWUSR | S_IRUGO, aw9120_ram_show, aw9120_ram_store);
static DEVICE_ATTR(blink, S_IWUSR | S_IRUGO, aw9120_blink_show, aw9120_blink_store);

static struct attribute* aw9120_attributes[] = {
    &dev_attr_reg.attr,
    &dev_attr_hwen.attr,
    &dev_attr_ram.attr,
    &dev_attr_blink.attr,
    NULL
};

static struct attribute_group aw9120_attribute_group = {
    .attrs = aw9120_attributes
};

static int aw9120_parse_led_cdev(struct aw9120* aw9120,
                                 struct device_node* np)
{
    struct device_node* temp;
    int ret = -1;

    for_each_child_of_node(np, temp) {
        ret = of_property_read_string(temp, "aw9120,name",
                                      &aw9120->cdev.name);

        if (ret < 0) {
            dev_err(aw9120->dev,
                    "Failure reading led name, ret = %d\n", ret);
            goto free_pdata;
        }

        ret = of_property_read_u32(temp, "aw9120,imax",
                                   &aw9120->imax);

        if (ret < 0) {
            dev_err(aw9120->dev,
                    "Failure reading imax, ret = %d\n", ret);
            goto free_pdata;
        }

        ret = of_property_read_u32(temp, "aw9120,brightness",
                                   &aw9120->cdev.brightness);

        if (ret < 0) {
            dev_err(aw9120->dev,
                    "Failure reading brightness, ret = %d\n", ret);
            goto free_pdata;
        }

        ret = of_property_read_u32(temp, "aw9120,max_brightness",
                                   &aw9120->cdev.max_brightness);

        if (ret < 0) {
            dev_err(aw9120->dev,
                    "Failure reading max brightness, ret = %d\n", ret);
            goto free_pdata;
        }
    }

    INIT_WORK(&aw9120->brightness_work, aw9120_brightness_work);

    aw9120->cdev.brightness_set = aw9120_set_brightness;
    ret = led_classdev_register(aw9120->dev, &aw9120->cdev);

    if (ret) {
        dev_err(aw9120->dev,
                "unable to register led ret=%d\n", ret);
        goto free_pdata;
    }

    ret = sysfs_create_group(&aw9120->cdev.dev->kobj,
                             &aw9120_attribute_group);

    if (ret) {
        dev_err(aw9120->dev, "led sysfs ret: %d\n", ret);
        goto free_class;
    }

    return 0;

free_class:
    led_classdev_unregister(&aw9120->cdev);
free_pdata:
    return ret;
}
#endif

/******************************************************
 *
 * misc drive fops
 *
 ******************************************************/
static void aw9120_all_blink(struct aw9120 * aw9120)
{
    unsigned char i;
    unsigned int reg_val;
    unsigned int imax = 0x1;

    imax = (imax << 12) | (imax << 8) |
           (imax << 4) | (imax << 0);
    //Disable LED Module
    aw9120_i2c_read(aw9120, REG_GCR, &reg_val);
    reg_val &= 0xFFFE;
    aw9120_i2c_write(aw9120, REG_GCR, reg_val);

    aw9120_i2c_write(aw9120, REG_IMAX1, imax);      // IMAX1-LED1~LED4 Current
    aw9120_i2c_write(aw9120, REG_IMAX2, imax);      // IMAX2-LED5~LED8 Current
    aw9120_i2c_write(aw9120, REG_IMAX3, imax);      // IMAX3-LED9~LED12 Current
    aw9120_i2c_write(aw9120, REG_IMAX4, imax);      // IMAX4-LED13~LED16 Current
    aw9120_i2c_write(aw9120, REG_IMAX5, imax);      // IMAX5-LED17~LED20 Current
    aw9120_i2c_write(aw9120, REG_LER1, 0x0FFF);     // LER1-LED1~LED12 Enable
    aw9120_i2c_write(aw9120, REG_LER2, 0x00FF);     // LER2-LED13~LED20 Enable
    aw9120_i2c_write(aw9120, REG_CTRS1, 0x0000);    // CTRS1-LED1~LED12: SRAM Control
    aw9120_i2c_write(aw9120, REG_CTRS2, 0x0000);    // CTRS2-LED13~LED20: SRAM Control

    //Enable LED Module
    reg_val |= 0x0001;
    aw9120_i2c_write(aw9120, REG_GCR, reg_val);     // GCR-Enable LED Module

    // LED SRAM Hold Mode
    aw9120_i2c_write(aw9120, REG_PMR, 0x0000);      // PMR-Load SRAM with I2C
    aw9120_i2c_write(aw9120, REG_RMR, 0x0000);      // RMR-Hold Mode

    //Load LED SRAM
    aw9120_i2c_write(aw9120, REG_WADDR, 0x0000);    // WADDR-SRAM Load Addr

    for (i = 0; i < led_code_len; i++) {
        aw9120_i2c_write(aw9120, REG_WDATA, led_code[i]);
    }

    // LED SRAM Run
    aw9120_i2c_write(aw9120, REG_SADDR, 0x0000);    // SADDR-SRAM Run Start Addr:0
    aw9120_i2c_write(aw9120, REG_PMR, 0x0001);      // PMR-Reload and Excute SRAM
    aw9120_i2c_write(aw9120, REG_RMR, 0x0002);      // RMR-Run

}

static void aw9120_led_blink(struct aw9120* aw9120, unsigned char blink, unsigned char index, uint8_t level)
{
    unsigned char i;
    unsigned int reg_val;
    unsigned int imax = 0;
    uint8_t addr1 = 0x0d; 
    uint8_t addr2 = 0x03;
    uint8_t addr3 = 0x0f;
    int commands[8] = {0};
    /*
    aw9120_blink_on_index(aw9120, index, level);
    return;
    aw9120_for_light_tmp(aw9120, index, level);
    */

    printk("%s enter...\n", __func__);
    aw9120->imax = 0x3;
    imax = (aw9120->imax << 12) | (aw9120->imax << 8) |
           (aw9120->imax << 4) | (aw9120->imax << 0);

    //Disable LED Module
    aw9120_i2c_read(aw9120, REG_GCR, &reg_val);
    reg_val &= 0xFFFE;
    aw9120_i2c_write(aw9120, REG_GCR, reg_val);     // GCR-Disable LED Module

    if (blink) {
        //LED Config
        aw9120_i2c_write(aw9120, REG_IMAX1, imax);      // IMAX1-LED1~LED4 Current
        aw9120_i2c_write(aw9120, REG_IMAX2, imax);      // IMAX2-LED5~LED8 Current
        aw9120_i2c_write(aw9120, REG_IMAX3, imax);      // IMAX3-LED9~LED12 Current
        aw9120_i2c_write(aw9120, REG_IMAX4, imax);      // IMAX4-LED13~LED16 Current
        aw9120_i2c_write(aw9120, REG_IMAX5, imax);      // IMAX5-LED17~LED20 Current
        aw9120_i2c_write(aw9120, REG_CTRS1, 0x0000);    // CTRS1-LED1~LED12: SRAM Control
        aw9120_i2c_write(aw9120, REG_CTRS2, 0x0000);    // CTRS2-LED13~LED20: SRAM Control
    
        aw9120_i2c_write(aw9120, REG_LER1, 0x0FFF);     // LER1-LED1~LED12 Enable
        aw9120_i2c_write(aw9120, REG_LER2, 0x00FF);     // LER2-LED13~LED20 Enable
        /*
        if (index >=1 || index <=12) {
            aw9120_i2c_read(aw9120, REG_LER1, &reg_val);
            reg_val |= (1 << (index -1));
            aw9120_i2c_write(aw9120, REG_LER1, reg_val);     // LER1-LED1~LED12 Enable
        } else if (index > 12 || index <= 20){
            aw9120_i2c_read(aw9120, REG_LER2, &reg_val);
            reg_val |= (1 << (index -13));
            aw9120_i2c_write(aw9120, REG_LER2, reg_val);     // LER2-LED13~LED20 Enable
        } else {
            printk("func %s error!\n", __func__);
        }
        */

        //Enable LED Module
        reg_val |= 0x0001;
        aw9120_i2c_write(aw9120, REG_GCR, reg_val);     // GCR-Enable LED Module

        // LED SRAM Hold Mode
        aw9120_i2c_write(aw9120, REG_PMR, 0x0000);      // PMR-Load SRAM with I2C
        aw9120_i2c_write(aw9120, REG_RMR, 0x0000);      // RMR-Hold Mode
        // Load LED SRAM
        aw9120_i2c_write(aw9120, REG_WADDR, 0x0000);    // WADDR-SRAM Load Addr

        commands[0] = (0x08 << 8) | (0xFF);
        commands[1] = (0x1c << 8) | addr1;

        commands[2] = (0x08 << 8) | (0xFF);
        commands[3] = (0x1c << 8) | addr2;

        commands[4] = (0x08 << 8) | (0xFF);
        commands[5] = (0x1c << 8) | addr3;

        if (index <= 7 || index >= 0) {

            commands[6] = (0x08 << 8) | (~(1 << index));
            commands[7] = (0x1c << 8) | addr1;

        }else if (index >= 8 || index <= 11) {

            commands[6] = (0x08 << 8) | (~(1 << (index - 8)));
            commands[7] = (0x1c << 8) | addr2;

        }else if (index <= 12 || index >= 19) {

            commands[6] = (0x08 << 8) | ~((1 << (index - 12)));
            commands[7] = (0x1c << 8) | addr3;

        }else{
           
            printk("func %s error!\n", __func__);
            return;

        }
        for (i = 1; i < 9; i++){
            blink_on_index_code[i] = commands[i - 1];
        }

        for (i = 0; i < blink_on_index_len; i++) {
            aw9120_i2c_write(aw9120, REG_WDATA, blink_on_index_code[i]);
        }

        // LED SRAM Run
        aw9120_i2c_write(aw9120, REG_SADDR, 0x0000);    // SADDR-SRAM Run Start Addr:0
        aw9120_i2c_write(aw9120, REG_PMR, 0x0001);      // PMR-Reload and Excute SRAM
        aw9120_i2c_write(aw9120, REG_RMR, 0x0002);      // RMR-Run
    }
}
static long aw9120_dev_unlocked_ioctl(struct file* filp,
                                      unsigned int cmd, unsigned long arg)
{
    uint8_t buf[2] = {0};
    struct aw9120* aw9120 = filp->private_data;

    switch (cmd) {
    case AW9120_CMD_ALL_BLINK:
        //aw9120_all_blink(aw9120);
        aw9120_led_blink(aw9120, 1, arg, 0);
        break;

    case AW9120_CMD_LIGHT:
        if(copy_from_user(buf, (uint8_t*)arg, 2) !=0){
            dev_err(&aw9120->i2c->dev, "cmd AW9120_CMD_LIGHT error\n");
            return -1;    
        }
        //pr_err("%s: index=%d level=%d\n", __func__, buf[0], buf[1]);
        if(buf[0] < 20 && buf[0] >= 0){
            aw9120_led_light(aw9120, buf[0], buf[1]);
        }else{
           return -1;
        }
        break;
    case AW9120_CMD_RESET:
        aw9120_hw_reset(aw9120);
        break;
    case AW9120_CMD_PWR:
        gpio_set_value(aw9120->reset_gpio, arg);
        break;
    default:
        dev_err(&aw9120->i2c->dev, "unknown cmd (%x, %lx)\n", cmd, arg);
    }
    return 0;
}

static ssize_t aw9120_dev_write(struct file* filp, const char __user* buf,
                               size_t count, loff_t* offset)
{
    struct aw9120* aw9120 = filp->private_data;
    int ret = 0;

    if ((ret = copy_from_user(aw9120->buf, buf, count)) != 0) {
        dev_err(&aw9120->i2c->dev, "copy from user error,rtn=%d\n", ret);
        return -EFAULT;
    }

    //printk("%s: reg(0x%02x)=0x%04x\n", __func__, buf[0], *(uint16_t*)&aw9120->buf[1]);
    mutex_lock(&aw9120->read_mutex);
    ret = aw9120_i2c_write(aw9120, aw9120->buf[0], *(uint16_t*)&aw9120->buf[1]);
    mutex_unlock(&aw9120->read_mutex);
    if (ret < 0) {
        dev_err(&aw9120->i2c->dev, "request write error,ret=%d\n", ret);
        ret = -EIO;
    }
    return count;
}

static ssize_t aw9120_dev_read(struct file* filp, char __user* buf,
                              size_t count, loff_t* offset)
{
    struct aw9120* aw9120 = filp->private_data;
    int ret = 0;
    unsigned int reg_val;

    if (count > MAX_BUFFER_SIZE) {
        dev_info(&aw9120->i2c->dev, "request read count=%d\n", (int)count);
        count = MAX_BUFFER_SIZE;
    }

    mutex_lock(&aw9120->read_mutex);
    ret = aw9120_i2c_read(aw9120, buf[0], &reg_val);
    mutex_unlock(&aw9120->read_mutex);

    if (ret < 0) {
        dev_err(&aw9120->i2c->dev, "failed read, rtn=%d\n", ret);
        return ret;
    }

    if (copy_to_user(buf, (uint8_t *)&reg_val, 2) != 0) {
        dev_err(&aw9120->i2c->dev, "failed to copy to user\n");
        return -EFAULT;
    }
    return count;
}

static int aw9120_dev_open(struct inode* inode, struct file* filp)
{
    struct aw9120* aw9120 = container_of(filp->private_data,
                                              struct aw9120, cdev);
    dev_info(&aw9120->i2c->dev, "device node major=%d,minor=%d",
             imajor(inode), iminor(inode));
    filp->private_data = aw9120;
#if LED_UI_DRIVER
    del_timer_sync(&aw9120->timer);
    flush_work(&aw9120->work_update);
    cancel_work_sync(&aw9120->work_update);
#endif
    return aw9120_dev_init(aw9120);
}

static const struct file_operations aw9120_dev_fops = {
    .owner = THIS_MODULE,
    .llseek = no_llseek,
    .read = aw9120_dev_read,
    .write = aw9120_dev_write,
    .open = aw9120_dev_open,
    .unlocked_ioctl = aw9120_dev_unlocked_ioctl
};

/******************************************************
 *
 * i2c driver
 *
 ******************************************************/
static int misc_device_register(struct aw9120* aw9120, struct device_node* np)
{
    int len;
    int ret;

    mutex_init(&aw9120->read_mutex);
    aw9120->cdev.minor = MISC_DYNAMIC_MINOR;
    aw9120->cdev.name = of_get_property(np, "dev_name", &len);
    aw9120->cdev.fops = &aw9120_dev_fops;
    ret = misc_register(&aw9120->cdev);
    mutex_init(&aw9120->read_mutex);
    if(ret != 0){
        dev_err(aw9120->dev, "register misc device errork,  ret: %d\n", ret);
        return ret;
    }
#if 0
    ret = sysfs_create_group(&aw9120->cdev.dev->kobj,
                             &aw9120_attribute_group);
    if (ret) {
        dev_err(aw9120->dev, "aw9120 sysfs error,  ret: %d\n", ret);
    }
#endif
    return ret;
}


struct aw9120* g_aw9120;

static int aw9120_i2c_probe(struct i2c_client* i2c, const struct i2c_device_id* id)
{
    struct aw9120* aw9120;
    struct device_node* np = i2c->dev.of_node;
    int ret;
    enum of_gpio_flags flags;
    printk("%s: i2c->addr = 0x%x\n", __func__, i2c->addr);

    if (!i2c_check_functionality(i2c->adapter, I2C_FUNC_I2C)) {
        dev_err(&i2c->dev, "check_functionality failed\n");
        return -EIO;
    }

    aw9120 = devm_kzalloc(&i2c->dev, sizeof(struct aw9120), GFP_KERNEL);
    g_aw9120 = aw9120;

    if (aw9120 == NULL) {
        return -ENOMEM;
    }
    
    aw9120->buf = kzalloc(MAX_BUFFER_SIZE, GFP_KERNEL);
    if (aw9120->buf == NULL) {
        kfree(aw9120);
        return -ENOMEM;
    }

    aw9120->dev = &i2c->dev;
    aw9120->i2c = i2c;

    /* aw9120 rst & int */
    if (np) {
        ret = aw9120_parse_dt(&i2c->dev, aw9120, np, &flags);
        if (ret) {
            dev_err(&i2c->dev, "failed to parse device tree node\n");
            goto err;
        }
    } else {
        aw9120->reset_gpio = -1;
    }

    if (gpio_is_valid(aw9120->reset_gpio)) {
        ret = amlogic_gpio_request(aw9120->reset_gpio, "aw9120_sdb");
        if (ret) {
            dev_err(&i2c->dev, "%s: rst request failed\n", __func__);
        } else {
            dev_err(&i2c->dev, "%s: reset gpio set ok\n", __func__);
        }
    } else {
        dev_err(&i2c->dev, "%s: reset gpio is invalid\n", __func__);
        goto err;
    }
    
    /* hardware reset */
    //aw9120_hw_reset(aw9120);

    /* aw9120 chip id */
    ret = aw9120_read_chipid(aw9120);
    if (ret < 0) {
        dev_err(&i2c->dev, "error, chipid=0x%04x, ret=%d\n", aw9120->chipid, ret);
        ret = -EINVAL;
        //goto err_id;
    }
    
    if (misc_device_register(aw9120, np)) {
        ret = -EINVAL;
        dev_err(&i2c->dev, "misc_register failed");
        goto err;
    }

    dev_set_drvdata(&i2c->dev, aw9120);
    i2c_set_clientdata(i2c, aw9120);
#if LED_UI_DRIVER
    aw9120->setup = false;
    INIT_WORK(&(aw9120->work_update), update_work_func);
    setup_timer(&aw9120->timer, aw9120_timer_sr, (unsigned long)aw9120) ;
    mod_timer(&aw9120->timer, jiffies + 100);
#endif
    
    aw9120->err_cnt = 0;
    pr_info("%s probe completed successfully!\n", __func__);
    return 0;

err_id:
err:
    if(aw9120 && aw9120->buf){
        kfree(aw9120->buf);
    }
    if(aw9120){ 
        kfree(aw9120);
    }
    return ret;
}

static int aw9120_remove(struct i2c_client* client)
{
    struct aw9120* dev;

    dev = i2c_get_clientdata(client);
#if LED_UI_DRIVER
    del_timer_sync(&dev->timer);
    flush_work(&dev->work_update);
    cancel_work_sync(&dev->work_update);
#endif
    misc_deregister(&dev->cdev);
    mutex_destroy(&dev->read_mutex);
    gpio_direction_output(dev->reset_gpio, 0);

    if (dev->buf != NULL) {
        kfree(dev->buf);
    }
    if (dev != NULL) {
        kfree(dev);
    }

    return 0;
}

static int aw9120_suspend(struct i2c_client* client, pm_message_t mesg)
{
    struct aw9120* dev;
    printk("aw9120_1_suspend\n");
    dev = i2c_get_clientdata(client);
#if LED_UI_DRIVER
    del_timer_sync(&dev->timer);
#endif
    gpio_direction_output(dev->reset_gpio, 0);

    return 0;
}
static int aw9120_resume(struct i2c_client* client)
{
    struct aw9120* dev;
    printk("aw9120_1_resume\n");
    dev = i2c_get_clientdata(client);
    aw9120_dev_init(dev);
    
    return 0;
}


static const struct i2c_device_id aw9120_i2c_id[] = {
    { AW9120_I2C_NAME, 0 },
    { }
};
MODULE_DEVICE_TABLE(i2c, aw9120_i2c_id);

static struct of_device_id aw9120_dt_match[] = {
    { .compatible = "awinic,aw9120_led" },
    { },
};

static struct i2c_driver aw9120_i2c_driver = {
    .driver = {
        .name = AW9120_I2C_NAME,
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(aw9120_dt_match),
    },
    .probe = aw9120_i2c_probe,
    .remove = aw9120_remove,
    .suspend = aw9120_suspend,
    .resume = aw9120_resume,
    .id_table = aw9120_i2c_id,
};


static int __init aw9120_i2c_init(void)
{
    int ret = 0;

    pr_info("aw9120 driver version %s\n", AW9120_VERSION);
    return i2c_add_driver(&aw9120_i2c_driver);
    return 0;
}
module_init(aw9120_i2c_init);


static void __exit aw9120_i2c_exit(void)
{
    pr_info("%s\n", __func__);
    gpio_free(g_aw9120->reset_gpio);
    return i2c_del_driver(&aw9120_i2c_driver);
}
module_exit(aw9120_i2c_exit);


MODULE_DESCRIPTION("AW9120 LED Driver");
MODULE_LICENSE("GPL v2");
