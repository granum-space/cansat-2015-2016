/*
 * spi.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void spi_init();
uint8_t spi_sendbyte(uint8_t arg);
void spi_exchange(const void* data, int length, uint8_t* retval);



#endif /* SPI_H_ */
