/*
 * common.h
 *
 *  Created on: 20 апр. 2016 г.
  */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// Подсчет контрольной суммы алгоритмом CRC-8
uint8_t crc8(const void * data_ptr, size_t data_size);

#endif /* COMMON_H_ */
