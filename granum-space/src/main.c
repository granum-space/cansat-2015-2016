/*
 * main.c
 *
 *  Created on: 09 апр. 2016 г.
 *      Author: developer
 */

#include <avr/io.h>
#include <util/delay.h>

#include "uart-debug.h"
#include "datautils.h"
#include "uart-debug.h"
#include "sd.h"
#include "spi.h"
#include "i2c.h"
#include "adc.h"
#include "onewire.h"
#include "1wdevices.h"
#include "pkt_types.h"
#include "radio-module.h"
#include "digipot.h"

int main()
{
	i2c_init();
	digipot_init();

	while(1)
	{
		digipot_write(128);
	}

	return 0;
}
