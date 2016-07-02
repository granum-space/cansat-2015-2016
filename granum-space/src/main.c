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
	initUartDebug();
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
	//soilres_init();
	spi_init();
	//TimeServiceInit();

	dtpkt_t pkt;


	while(1){

		//GR_DEBUG("From opt%d, error %d\n",optdata,error);

	}
}

/*int main()
{
	_delay_ms(5000);
	DDRG = 0xFF;
	PORTG = 0xFF;
	initUartDebug();
	GR_DEBUG("Debug init completed!");
	du_init();
	GR_DEBUG("DU init completed!");
	adc_init();
	GR_DEBUG("ADC init completed!");
	OneWireInit();
	GR_DEBUG("1wire init completed!");
	GR_DEBUG("All inits completed!");
	dtpkt_t pkt;
	pkt.beacon = 0xFFFF;
	pkt.number = 0;
	pkt.time = 0;
	pkt.time_part = 0;
	pkt.temperature2 = 0;
	pkt.humidity = 0;
	pkt.O2 = 0;
	pkt.CO2 = 0;
	pkt.rezistance12 = 0;
	pkt.rezistance13 = 0;
	pkt.rezistance23 = 0;
	pkt.legs = 0;
	pkt.parachute = 0;
	timeData_t timed;
	while(1) {
		pkt.number++;
		pkt.temperature1 = get_temperature();
		pkt.pressure = adc_read(ADC_CHANNEL_PRESSURE);
		pkt.rezistance12 = adc_read(ADC_CHANNEL_EARTH_TEMP_1);
		pkt.rezistance13 = adc_read(ADC_CHANNEL_EARTH_TEMP_2);
		pkt.rezistance23 = adc_read(ADC_CHANNEL_EARTH_TEMP_3);
		timed = TimeServiceGet();
		pkt.time = timed.seconds;
		pkt.time_part = timed.subseconds;
		uint8_t* pkt_ptr = (uint8_t*)&pkt;
		pkt.cntrl = 0;
		for(int i = 0; i < (sizeof(pkt)-sizeof(pkt.cntrl)); i++) {
			pkt.cntrl += *(pkt_ptr+i);
		}
		du_write(pkt_ptr, sizeof(pkt));
		//GR_DEBUG("SMPFOMPOFKW");
	}

	return 0;
}*/



