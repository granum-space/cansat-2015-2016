/*
 * adc.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

// Инициализация модуля АЦП
void adc_init();

// Чтеные результата преборазования модуля АЦП.
// Аргумент - номер вывода
uint16_t adc_read(uint8_t pinNumber);


#endif /* ADC_H_ */
