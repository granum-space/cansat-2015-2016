/*
 * radio-module.h
 *
 *  Created on: 23 мая 2016 г.
 *      Author: developer
 */

#ifndef RADIO_MODULE_H_
#define RADIO_MODULE_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void radio_init();
void radio_write(const uint8_t *value, size_t size);


#endif /* RADIO_MODULE_H_ */
