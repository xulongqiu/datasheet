#ifndef __AW9110_EXT_PROBE__
#define __AW9110_EXT_PROBE__
#include <linux/list.h>
#include <linux/i2c.h>

#define AML_I2C_BUS_AO 0
#define AML_I2C_BUS_A 1
#define AML_I2C_BUS_B 2
#define AML_I2C_BUS_C 3
#define AML_I2C_BUS_D 4

#define NAME_SIZE 32

typedef struct {
	const char* name;
	const char* status;
	unsigned i2c_bus_type;
	unsigned i2c_addr;
	unsigned id_reg;
	unsigned id_val;
}aw9110_dev_info_t;


#endif
