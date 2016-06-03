/*
 * Digipot.c

 *
 *  Created on: 26 мая 2016 г.
 *      Author: developer
 */

#include "Digipot.h"

#include <avr/io.h>
#include <util/delay.h>


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

#define I2C_TIMEOUT_COUNT 30
#define I2C_TIMEOUT_US 10

#define F_SCL 600000         // подправить не нужные макросы



i2c_error_t i2c_status_to_error_digipot(uint8_t status)    // подправить не нужные макросы
{
	switch (status)
	{
	case I2C_ARB_LOST:
		return I2C_arb_lost;

	case I2C_SLAW_NO_ACK:
	case I2C_SLAR_NO_ACK:
		return I2C_nack_recivied;

	case I2C_WRITE_NO_ACK:
	case I2C_READ_NO_ACK:
		return I2C_nack_recivied;

	};

	return I2C_wrong_status;
}



int i2c_start_digipot()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	for(int i = 0; i < I2C_TIMEOUT_COUNT; i++){
		if (TWCR & (1<<TWINT)) {
			uint8_t status = TWSR & 0xF8;
			if (status == I2C_START_TRANSFERED || status == I2C_RESTART_TRANSFERED)	{
				return 0;
			} else {
				return i2c_status_to_error(status);
			}
		}
	}
	return I2C_timeout;
}



int i2c_send_slaw_digipot(uint8_t slave_addr, bool read_access)
{
	TWDR = (slave_addr << 1) | read_access;
	TWCR = (1<<TWINT) | (1<<TWEN);

	for(int i = 0; i < I2C_TIMEOUT_COUNT; i++ ) {
		if (TWCR & (1<<TWINT)) {
			uint8_t status = TWSR & 0xF8;
			if (status == I2C_SLAW_ACK || status == I2C_SLAR_ACK) {
				return 0;
			} else {
				return i2c_status_to_error(status);
			}
		} else {
			_delay_us(I2C_TIMEOUT_US);
		}
	}

	return I2C_timeout;
}

int configuration_byte(){
	uint8_t configuration[8];
	uint8_t *p;
	*p = configuration;
	*p = 0;
	*(p+1) = 1;
	*(p+2) = 0;
	*(p+3) =  ;
	*(p+4) = ;
	*(p+5) = *(p+6) = *(p+7) = 0;


}











int i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	return 0;
}




