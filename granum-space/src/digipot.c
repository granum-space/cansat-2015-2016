/*
 * digipot.c
 *
 *  Created on: 28 мая 2016 г.
 *      Author: developer
 */

#include "digipot.h"


#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "config.h"
#include "i2c.h"
#include "uart-debug.h"

bool digipot_needinit = true;

uint8_t digipot_pos;

void digipot_init(){
	if(digipot_needinit){
		digipot_needinit = false;
	}
}


int digipot_write(uint8_t position)
{
	digipot_pos = position;
	i2c_start();
	i2c_send_slaw(0x01, 1);

	uint8_t conf[8] = {0};
	uint8_t cfg_byte = 0;
	for(uint8_t i = 0; i < 8; i++){
		cfg_byte |= (conf[i] << i);
	}

	i2c_write(&cfg_byte, 1);
	i2c_write(&position, 1);

	i2c_stop();
	return 0;
}

