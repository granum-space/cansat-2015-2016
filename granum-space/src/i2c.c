#include "i2c.h"


void i2c_init()
{




}


int i2c_start()
{




	return 0;
}


int i2c_stop()
{



	return 0;
}


int i2c_send_slaw(uint8_t slave_addr, bool read_access)
{




	return 0;
}



int i2c_write(const void * data_ptr, size_t data_size)
{
	const uint8_t * byte_ptr = (const uint8_t * )data_ptr;

	return 0;
}


int i2c_read(void * data_ptr, size_t data_size)
{
	uint8_t * byte_ptr = (uint8_t * )data_ptr;

	// не забудь тут про NACK

	return 0;
}

