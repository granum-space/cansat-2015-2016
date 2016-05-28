/*
 * digipot.h
 *
 *  Created on: 28 мая 2016 г.
 *      Author: developer
 */

#ifndef DIGIPOT_H_
#define DIGIPOT_H_

#include "i2c.h"


void i2c_init_digipot();

int write_digipot(uint8_t position);

#endif /* DIGIPOT_H_ */
