/*
 * soilres.h
 *
 *  Created on: 26 июня 2016 г.
 *      Author: developer
 */

#ifndef SOILRES_H_
#define SOILRES_H_
#include <stdint.h>
void soilres_init();

int8_t soilres_get(int16_t * adiff);

typedef struct {
	uint8_t res12, res23, res31;
	int16_t diff12, diff23, diff31;
} soilres_t;

#endif /* SOILRES_H_ */
