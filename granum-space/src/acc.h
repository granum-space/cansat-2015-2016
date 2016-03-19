/*
 * acc.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef ACC_H_
#define ACC_H_

#include <stdint.h>
#include <stddef.h>

void acc_init();

uint16_t acc_availible();
uint16_t acc_read(uint16_t * data, size_t dataSize);


#endif /* ACC_H_ */
