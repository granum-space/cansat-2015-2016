/*
 * adc.c
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */


#include "adc.h"

#include <avr/io.h>

void adc_init()
{
	ADMUX = (1 << REFS0) | (0 << REFS1) // опорное напряжение на AVCC
		| (0 << ADLAR) // Левосторонний формат результата
	;
	ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADIE) |
			(0 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

}


uint16_t adc_read(adc_channel_t channel)
{
	ADMUX &= ~((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3));

#ifdef __AVR_ATmega328P__
	switch(channel)
	{
	case ADC_CHANNEL_PRESSURE:
		ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (0 << MUX3);
		break;

	case ADC_CHANNEL_EARTH_TEMP_1:
		ADMUX |= (0 << MUX0) | (0 << MUX1) | (1 << MUX2) | (0 << MUX3);
		break;

	case ADC_CHANNEL_EARTH_TEMP_2 :
	    ADMUX |= (0 << MUX0) | (1 << MUX1) | (0 << MUX2) | (0 << MUX3);
	  break;

	case ADC_CHANNEL_EARTH_TEMP_3 :
		ADMUX |= (1 << MUX0) | (1 << MUX1) | (0 << MUX2) | (0 << MUX3);
	break;

	case ADC_CHANNEL_EARTH_RES:
		ADMUX |= (1 << MUX0) | (0 << MUX1) | (0 << MUX2) | (1 << MUX3);
	  break;

	case ADC_CHANNEL_O2_SENS :
		ADMUX |= (1 << MUX0) | (0 << MUX1) | ( 1 << MUX2) | (0 << MUX3);
	break;

	case ADC_CHANNEL_CO2_SENS :
		ADMUX |= (0 << MUX0) | (1 << MUX1) | ( 1 << MUX2) | (0 << MUX3);
	break;
	};

#elif defined __AVR_ATmega128__
	switch(channel)
	{
	case ADC_CHANNEL_PRESSURE:
		ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (0 << MUX3) | (0 << MUX4);
		break;

	case ADC_CHANNEL_EARTH_TEMP_1:
		ADMUX |= (0 << MUX0) | (0 << MUX1) | (1 << MUX2) | (0 << MUX3) | (0 << MUX4);
		break;

	case ADC_CHANNEL_EARTH_TEMP_2 :
	    ADMUX |= (0 << MUX0) | (1 << MUX1) | (0 << MUX2) | (0 << MUX3) | (0 << MUX4);
	  break;

	case ADC_CHANNEL_EARTH_TEMP_3 :
		ADMUX |= (1 << MUX0) | (1 << MUX1) | (0 << MUX2) | (0 << MUX3) | (0 << MUX4);
	break;

	case ADC_CHANNEL_EARTH_RES:
		ADMUX |= (1 << MUX0) | (0 << MUX1) | (0 << MUX2) | (1 << MUX3) | (0 << MUX4);
	  break;

	case ADC_CHANNEL_O2_SENS :
		ADMUX |= (1 << MUX0) | (0 << MUX1) | ( 1 << MUX2) | (0 << MUX3) | (0 << MUX4);
	break;

	case ADC_CHANNEL_CO2_SENS :
		ADMUX |= (0 << MUX0) | (1 << MUX1) | ( 1 << MUX2) | (0 << MUX3) | (0 << MUX4);
	break;

	default:
	};

#endif
	ADCSRA |= (1 << ADSC);

	while(1){
		if ((ADCSRA & (1 << ADIF)) != 0)
		{
			uint16_t value = ADC;
			return value;
		}
		else
		{
			continue;
		}
	}

	return 0;
}
