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

uint8_t acc_read(int16_t * datax,int16_t * datay,int16_t * dataz);


#endif /* ACC_H_ */
