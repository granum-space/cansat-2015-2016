/*
 * soilres.c

 *
 *  Created on: 26 июня 2016 г.
 *      Author: developer
 */
#include <stdbool.h>

#include "soilres.h"
#include "adc.h"
#include "digipot.h"
#include "config.h"

bool soilres_needinit = true;

soilres_t resdata;

void soilres_init() {
	if(soilres_needinit){
		adc_init();
		SRDDR |= (1<<SR1MODE)|(1<<SR1ON)|(1<<SR2MODE)|(1<<SR2ON)|(1<<SR3MODE)|(1<<SR3ON);
		resdata.res12 = 128;
		resdata.res23 = 128;
		resdata.res31 = 128;
		resdata.diff12 = 0;
		resdata.diff23 = 0;
		resdata.diff31 = 0;
		soilres_needinit = false;
	}
}

void legOff(int8_t leg) {
	switch(leg) {
	case 1: PORTA &= ~(1<<SR1ON);
			break;
	case 2: PORTA &= ~(1<<SR2ON);
			break;
	case 3: PORTA &= ~(1<<SR3ON);
			break;
	}
}

void legOn(int8_t leg, int8_t state) {
	switch(leg) {
	case 1: PORTA |= (1<<SR1ON);
			if(state) {
				PORTA |= (1<<SR1MODE);
			}
			else {
				PORTA &= ~(1<<SR1MODE);
			}
			break;
	case 2: PORTA |= (1<<SR2ON);
			if(state) {
				PORTA |= (1<<SR2MODE);
			}
			else {
				PORTA &= ~(1<<SR2MODE);
			}
			break;
	case 3: PORTA |= (1<<SR3ON);
			if(state) {
				PORTA |= (1<<SR3MODE);
			}
			else {
				PORTA &= ~(1<<SR3MODE);
			}
			break;
	}
}

void soilres_update() {
	legOff(1);
	legOff(2);
	legOff(3);
	legOn(1, 0);
	legOn(2, 1);
	digipot_write((resdata.res12 + (resdata.diff12/10)));
	resdata.res12 = digipot_pos;
	resdata.diff12 = adc_read(ADC_CHANNEL_EARTH_RES);
	legOff(1);
	legOn(3, 0);
	digipot_write((resdata.res23 + (resdata.diff23/10)));
	resdata.res23 = digipot_pos;
	resdata.diff23 = adc_read(ADC_CHANNEL_EARTH_RES);
	legOff(2);
	legOn(1, 1);
	digipot_write((resdata.res31 + (resdata.diff31/10)));
	resdata.res31 = digipot_pos;
	resdata.diff31 = adc_read(ADC_CHANNEL_EARTH_RES);
	legOff(1);
	legOff(3);
}




