/*
 * humidity.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <stdint.h>

typedef struct
{
	uint16_t humidity;
	uint16_t temperature;
} HTData;

uint16_t get_temperature();
HTData get_dht_data();

#endif /* HUMIDITY_H_ */


