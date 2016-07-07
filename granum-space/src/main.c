/*
 * main.c
 *
 *  Created on: 09 апр. 2016 г.
 *      Author: developer
 */

#include <avr/io.h>
#include <avr/interrupt.h>
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
//#include "opt3001.h"
#include "pkt_types.h"
#include "radio-module.h"
#include "sd.h"
#include "soilres.h"
#include "spi.h"
#include "time.h"
#include "uart.h"
#include "uart-debug.h"

timeData_t TempTime;

uint16_t temp_startOfConv;
timeData_t startOfConv_time;

timeData_t startOfSeeds_time;
bool SeedStarted = 0;

//timeData_t BigLuxTime;
//bool isBigLux;
//bool needCloseLEGFR = 0;

bool Started = false;

uint16_t PresBuf[5];
int PresBufi;
bool WaitLand = false;

int main(){
	//It's inits time!
	initUartDebug();
	DDRG = 0xFF;
	acc_init();
	PORTG = 0xFF;
	adc_init();
	//burn_init();
	du_init();
	DHT_Init();
	//digipot_init();
	//GPS_Init();
	i2c_init();
	OneWireInit();
	//OPT_init();
	radio_init();
	sd_init();
	//soilres_init();
	spi_init();
	TimeServiceInit();
	dtpkt_t pkt;
	/*accpkt_t accpkt;
	accpkt.beacon = 0xACCC;
	accpkt.number = 0;
	accpkt.entries = 0;

	uint8_t dataaval=0;*/

	pkt.beacon = 0xFFFF;
	pkt.number = 0;

	cli();
	start_temperature();

	//isBigLux = false;

	sei();
	_delay_ms(1);
//	uint16_t opt_devid = 0;;
//	OPT_read(0x7F, &opt_devid);
//	GR_DEBUG("OPT DevID = 0x%02x\n", opt_devid);TempTime = TimeServiceGet();
	pkt.humidity = 0;
	pkt.temperature2 = 0;
	while(1){
		PORTG ^= 0xFF;
		/*for(int i = 0;i<1;i++) {
			dataaval = acc_read(accpkt.datax,accpkt.datay,accpkt.dataz);
			TempTime = TimeServiceGet();
			accpkt.time = TempTime.seconds;
			accpkt.time_part = TempTime.subseconds;
			if(dataaval) {
				accpkt.entries = dataaval;
				accpkt.number++;
				du_write(&accpkt, 9);
				du_write(accpkt.datax, dataaval);
				du_write(accpkt.datay, dataaval);
				du_write(accpkt.dataz, dataaval);
				for(int i = 0; i < (sizeof(accpkt)-sizeof(accpkt.cntrl)); i++) {
					accpkt.cntrl += *((uint8_t*)(&accpkt)+i);
				}
				du_write(&accpkt.cntrl, 2);
			}
		}*/
		TempTime = TimeServiceGet();
		if(TempTime.seconds-startOfConv_time.seconds){
			cli();
			pkt.temperature1 = get_temperature();
			sei();
			startOfConv_time = TimeServiceGet();
		}
		cli();
		DHT_Read(&pkt.humidity,&pkt.temperature2);
		sei();
//		if (rc != 0)
//			GR_DEBUG("dht22 error = %d\n", rc);
		pkt.pressure = adc_read(ADC_CHANNEL_PRESSURE);
		pkt.O2 = adc_read(ADC_CHANNEL_O2_SENS);
		pkt.CO2 = adc_read(ADC_CHANNEL_CO2_SENS);
		//OPT_result(&pkt.lum);
		TempTime = TimeServiceGet();
		pkt.time = TempTime.seconds;
		pkt.time_part = TempTime.subseconds;
		pkt.number++;
		for(int i = 0; i < (sizeof(pkt)-sizeof(pkt.cntrl)); i++) {
				pkt.cntrl += *((uint8_t*)(&pkt)+i);
		}
		du_write(&pkt, sizeof(pkt));
		//GR_DEBUG("Number %d, %d sec %d subsec, temp1 %d, temp2 %d, pres %d, hum %d, O2 %d, CO2 %d, lum %d\n", pkt.number, pkt.time, pkt.time_part, pkt.temperature1,pkt.temperature2,pkt.pressure,pkt.humidity,pkt.O2,pkt.CO2,pkt.lum);

		/*dataaval = acc_read(accpkt.datax,accpkt.datay,accpkt.dataz);
		TempTime = TimeServiceGet();
		accpkt.time = TempTime.seconds;
		accpkt.time_part = TempTime.subseconds;
		if(dataaval) {
			accpkt.entries = dataaval;
			accpkt.number++;
			du_write(&accpkt, 9);
			du_write(accpkt.datax, dataaval);
			du_write(accpkt.datay, dataaval);
			du_write(accpkt.dataz, dataaval);
			for(int i = 0; i < (sizeof(accpkt)-sizeof(accpkt.cntrl)); i++) {
				accpkt.cntrl += *((uint8_t*)(&accpkt)+i);
			}
			du_write(&accpkt.cntrl, 2);
		}*/
		if(OnLaunchpad) {
			if(StartPres - adc_read(ADC_CHANNEL_PRESSURE) > 20) {
				OnLaunchpad = 0;
				Started = 1;
			}
		}
		if(Started){
			if(WaitLand){
				int treshhold = 1;
				PresBuf[PresBufi] = pkt.pressure;
				bool onePres = 1;
				for(int i = 1;i<5;i++){
					if((PresBuf[0]-PresBuf[i]>treshhold)||(PresBuf[i]-PresBuf[0])>treshhold) onePres=0;
				}
				if(onePres){
					FRPORT |= (1<<FRSEEDS);
					Started = 0;
					SeedStarted = 1;
					startOfSeeds_time = TimeServiceGet();
				}
			}
			PresBuf[PresBufi] = pkt.pressure;
			if(PresBufi == 4) {
				PresBufi = 0;
				WaitLand = 1;
			}
			else PresBufi++;
		}
		if(SeedStarted){
			if(startOfSeeds_time.seconds - TimeServiceGet().seconds) {
				FRPORT &= ~(1<<FRSEEDS);
				SeedStarted = 0;
				pkt.seeds = 1;
			}
		}
		_delay_ms(900);
	}
}

/*int main() { //testing acc
	_delay_ms(1000);
	initUartDebug();
	GR_DEBUG("I'm alive!\n");
	acc_init();
	int16_t datax[33];
	int16_t datay[33];
	int16_t dataz[33];
	uint8_t dataaval=0;
	while(true) {
		dataaval = acc_read(datax,datay,dataz);
		for(int i=0;i<dataaval;i++) {
			//GR_DEBUG("%f,%f,%f\n",((float)datax[i]*4.0f/1000.0f),((float)datay[i]*4.0f/1000.0f),((float)dataz[i]*4.0f/1000.0f));
			GR_DEBUG("%d,%d,%d\n",datax[i],datay[i],dataz[i]);
		}
		GR_DEBUG("%d entries\n",dataaval);
		//_delay_ms(50);
		//_delay_ms(10);
	}
}*/

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
		start_temperature();
		//_delay_ms(1000);
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
		GR_DEBUG("SMPFOMPOFKW");
	}

	return 0;
}*/



