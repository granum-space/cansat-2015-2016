/*
 * main.c
 *
 *  Created on: 09 апр. 2016 г.
 *      Author: developer
 */
#include <util/delay.h>
#include "uart_stdio.h"
#include "sd.h"
#include "spi.h"

int main()
{
	initUartStdio();

	//while(1) {
		_delay_ms(100);
		while(1) {
			//DEBUG("It finally answered %d\n", sd_init());
			if(sd_init()==0x00) {
				break;
			}
		}
		uint8_t CMD24[] = {
					0x58,
					0x00,
					0x00,
					0x02,
					0x00,
					0x00 //CRC8
			};
		spi_exchange(CMD24, sizeof(CMD24),0);
		uint8_t answer;
		while(1) {
			answer = spi_sendbyte(0xFF);
			DEBUG("It sayed %d\n", answer);
			if(answer == 0x00) break;
		}
		spi_sendbyte(0xFF);
		DEBUG("Sending data\n");
		spi_sendbyte(~(1));
		for(int i = 0;i<512;i++) {
			spi_sendbyte((uint8_t)/*(i & 0xFF)*/0xFC);
		}
		spi_sendbyte(0xFF);
		spi_sendbyte(0xFF);
		answer = spi_sendbyte(0xFF);
		DEBUG("It told %d\n", answer);
		while(1)spi_sendbyte(0xFF);
	//}
	return 0;
}
