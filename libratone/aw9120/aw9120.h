#ifndef _AW9120_H_
#define _AW9120_H_

#define MAX_I2C_BUFFER_SIZE 12

#define AW9120_ID 0xb223
#define AW9120_SYS_LED 0
#define AW9120_MISC_LED 1
//#define LED_UI_DRIVER 1
struct aw9120 {
    struct mutex read_mutex;
    struct i2c_client *i2c;
    struct device *dev;
#if AW9120_SYS_LED
    struct led_classdev cdev;
#elif AW9120_MISC_LED
    uint8_t* buf;
#if LED_UI_DRIVER
    struct timer_list timer;
    struct work_struct work_update;
    bool   setup;
#endif
   struct miscdevice cdev;
#endif
    struct work_struct brightness_work;

    int reset_gpio;

    unsigned int chipid;
    uint16_t err_cnt;
    int imax;
};

#endif

