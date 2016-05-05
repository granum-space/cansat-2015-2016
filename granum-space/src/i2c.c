#include "i2c.h"

#include <avr/io.h>


void i2c_init()
{




}
	i2c_error_value_t;


int i2c_start()
{
	i2c_error_value_t = 1;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	for(int i = 0; i < 7;i++){
	if (!(TWCR & (1<<TWINT)))
		return 0;
	}

	return I2C_stop_Time_Out;
}


int i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);


	if( TWCR != (1<<TWINT)|(1<<TWEN)|(1<<TWSTO))
		return I2C_stop_Time_Out;

	return 0;
}


int i2c_send_slaw(uint8_t slave_addr, bool read_access)
{
	uint8_t Addres
	read_access = false;
	uint8_t
	TWDR = Addres;
	TWCR = (1<<TWINT) | (1<<TWEN);
	if (!(TWCR & (1<<TWINT)))
		 return 0;
	else return I2C_stop_Time_Out;





}



int i2c_write(const void * data_ptr, size_t data_size)
{
	const uint8_t * byte_ptr = (const uint8_t * )data_ptr;

	return 0;
}


int i2c_read(void * data_ptr, size_t data_size, bool NACK_at_end)
{
	uint8_t * byte_ptr = (uint8_t * )data_ptr;

	// не забудь тут про NACK

	return 0;
}

