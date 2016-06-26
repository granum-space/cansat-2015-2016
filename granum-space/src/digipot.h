/*
 * digipot.h
 *
 *  Created on: 28 мая 2016 г.
 *      Author: developer
 */

#ifndef DIGIPOT_H_
#define DIGIPOT_H_

#include "i2c.h"

extern uint8_t digipot_pos;

void digipot_init();

int digipot_write(uint8_t position);

#endif /* DIGIPOT_H_ */
