/*
 * adc.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef enum
{
	ADC_CHANNEL_PRESSURE, //ADC7
	ADC_CHANNEL_EARTH_TEMP_1, //ADC4
	ADC_CHANNEL_EARTH_TEMP_2, //ADC2
	ADC_CHANNEL_EARTH_TEMP_3, //ADC3
	ADC_CHANNEL_EARTH_RES, //ADC1-ADC0
	ADC_CHANNEL_O2_SENS, //ADC5
	ADC_CHANNEL_CO2_SENS //ADC6
} adc_channel_t;


// Инициализация модуля АЦП
void adc_init();

// Чтеные результата преборазования модуля АЦП.
// Аргумент - номер вывода
int16_t adc_read(adc_channel_t channel);


#endif /* ADC_H_ */
