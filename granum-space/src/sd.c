/*
 * sd.c

 *
 *  Created on: 15 апр. 2016 г.
 *      Author: developer
 */
#include <stdint.h>

#include "spi.h"

uint8_t sd_send_r1cmd(uint8_t cmd, uint32_t arg, uint8_t crc);

void sd_init() {
	spi_init();
	uart_send(0xbe);
	for(int i=0;i<10;i++) {
		spi_sendbyte(0xFF);
	}
}

uint8_t sd_send_r1cmd(uint8_t cmd, uint32_t arg, uint8_t crc) {
	spi_sendbyte((0x40+cmd));
	spi_sendbyte(*(((uint8_t*)&arg)));
	spi_sendbyte(*(((uint8_t*)&arg)+1));
	spi_sendbyte(*(((uint8_t*)&arg)+2));
	spi_sendbyte(*(((uint8_t*)&arg)+3));
	spi_sendbyte(crc);
	uint8_t answer = 0xFF;
	while(answer==0xFF){answer=spi_sendbyte(0xFF);}
	return answer;
}
