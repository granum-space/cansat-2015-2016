/*
 * sd.c

 *
 *  Created on: 15 апр. 2016 г.
 *      Author: developer
 */
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdbool.h>

#include "uart-debug.h"
#include "spi.h"
#include "config.h"

bool sd_needinit = true;

uint8_t sd_send_r1cmd(uint8_t cmd, uint32_t arg, uint8_t crc);
void sd_enable();
void sd_disable();

uint8_t sd_init() {
	uint8_t answer;
	if(sd_needinit){
		spi_init();
		SPIDDR |= (1<<SS);
		SPIPORT |= (1<<SS);
		sd_disable();
		for(int i=0;i<20;i++) {
			spi_sendbyte(0xFF);
		}
		sd_enable();
		uint8_t CMD0[] = {
			1<<6,
			0x00,
			0x00,
			0x00,
			0x00,
			0x95 //CRC8
		};
		spi_exchange(CMD0, sizeof(CMD0),0);
		for(int i = 0; i<16;i++) {
			answer = spi_sendbyte(0xFF);
			GR_DEBUG("It answered %d\n", answer);
			if(answer != 0xFF) break;
		}
		GR_DEBUG("CMD0 answer %d\n", answer);
		if(answer != 0x01) return answer;
		uint8_t CMD1[] = {
				0x41,
				0x00,
				0x00,
				0x00,
				0x00,
				0x00 //CRC8
		};
		for(int i=0;i<20;i++) {
			spi_exchange(CMD1, sizeof(CMD1),0);
			for(int ii=0;ii<10;ii++) {
				answer = spi_sendbyte(0xFF);
				if(answer != 0xFF) break;
			}
			GR_DEBUG("CMD1 answer %d\n", answer);
			if(answer == 0x00) break;
		}
		sd_needinit = false;
	}
	else answer = 0x00;
	return answer;
	//if(answer != 0) return answer;

}



void sd_enable() {
	SPIPORT &= ~(1<<SS);
	_delay_ms(1);
}

void sd_disable() {
	SPIPORT |= (1<<SS);
	_delay_ms(1);
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
