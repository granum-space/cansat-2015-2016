/*
 * main.c
 *
 *  Created on: 09 апр. 2016 г.
 *      Author: developer
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "1wdevices.h"
#include "acc.h"
#include "adc.h"
#include "burn.h"
#include "config.h"
#include "datautils.h"
#include "dht022.h"
#include "digipot.h"
#include "gps.h"
#include "i2c.h"
#include "onewire.h"
#include "opt3001.h"
#include "pkt_types.h"
#include "radio-module.h"
#include "sd.h"
#include "soilres.h"
#include "spi.h"
#include "time.h"
#include "uart.h"
#include "uart-debug.h"

int main(){
	//It's inits time!
	acc_init();
	adc_init();
	//burn_init();
	du_init();
	DHT_Init();
	digipot_init();
	GPS_Init();
	i2c_init();
	OneWireInit();
	OPT_init();
	radio_init();
	sd_init();
	soilres_init();
	spi_init();
	TimeServiceInit();
	uart_init();
	initUartDebug();
}


