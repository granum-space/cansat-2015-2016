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
#include "acc.h"
#include "onewire.h"
#include "1wdevices.h"
#include "pkt_types.h"
#include "radio-module.h"
#include "dht022.h"
#include "opt3001.c"
#include "opt3001.h"

int main(){
	OPT_init();
	OPT_check();

	while(1)
		OPT_RESULT();
}


