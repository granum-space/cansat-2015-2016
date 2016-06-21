/*
 * acc.c
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#include "config.h"
#include "i2c.h"

void acc_init() {
	i2c_init();
	i2c_start();
	i2c_send_slaw(ACC_ADRESS, false);
}

void acc_writereg(uint8_t registry, const void * data_ptr, size_t data_size) {
	i2c_write(&registry, 1);
	i2c_write(data_ptr, data_size);
}
