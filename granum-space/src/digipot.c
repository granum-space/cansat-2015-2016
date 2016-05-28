/*
 * digipot.c
 *
 *  Created on: 28 мая 2016 г.
 *      Author: developer
 */

#include "digipot.h"


#include <avr/io.h>
#include <util/delay.h>

#include "config.h"
#include "uart-debug.h"

#define I2C_START_TRANSFERED 0x10
#define I2C_RESTART_TRANSFERED 0x08
#define I2C_SLAW_ACK 0x18
#define I2C_SLAW_NO_ACK 0x20
#define I2C_SLAR_ACK 0x40
#define I2C_SLAR_NO_ACK 0x48
#define I2C_READ_ACK 0x50
#define I2C_READ_NO_ACK 0x58
#define I2C_WRITE_ACK 0x28
#define I2C_WRITE_NO_ACK 0x30
#define I2C_ARB_LOST 0x38



void i2c_init_digipot(){

}

int i2c_start();

int i2c_send_slaw(uint8_t slave_addr, bool read_access);

int i2c_write(const void * data_ptr, size_t data_size);




int sending_digipot(uint8_t position){

	uint8_t conf[8];

	for(uint8_t i = 0; i < 8; i++){
		conf[i] = (conf[i] << i);
	}
	uint8_t position_digipot[8];

	for(uint8_t i = 0;i < 8; i++){
		position_digipot[i]= position;
	}
	i2c_write(conf , 8);
	i2c_write(position_digipot, 8);
	return 0;

}

int i2c_stop();


