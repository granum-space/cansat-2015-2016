/*
 * humidity.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <stdint.h>
#include <stddef.h>

int32_t get_temperature();

// Подсчет контрольной суммы алгоритмом CRC-8
uint8_t crc8(const void * data_ptr, size_t data_size);

enum{
	crc_error = -1,  // Возвращает в случае несовпадения crc
	reset_error = -2, // возвращает если устройсво не ответило нам
};

#endif /* HUMIDITY_H_ */


