

#include <util/delay.h>
#include <avr/io.h>

#include "spi.h"
#include "sd.h"
#include "uart-debug.h"
#include "uart.h"

#define RCFGPORT PORTC
#define RCFGDDR DDRC
#define RCFGNUM 0

uint32_t block = 0;
uint16_t bib = 0;

void du_init() {
	uart_init();
	RCFGDDR |= (1<<RCFGNUM);
	RCFGPORT |= (1<<RCFGNUM);
	_delay_us(1);
	RCFGPORT &= ~(1<<RCFGNUM);
	uint8_t config[] = {
			0x7E,0x7E,0x7E,0x7E, //destination address
			0x7E,0x7E,0x7E,0x7E //self address
	};
	uart_send_many(config, sizeof(config));
	RCFGPORT |= (1<<RCFGNUM);
	while(1) {
		if(sd_init()==0x00) {
			break;
		}
		_delay_ms(100);
	}
}

void du_write(const void* data, int length) {
	const uint8_t* ptr = (const uint8_t*) data;
	for(int i = 0; i < length; i++) {
		uart_send(*(ptr+i));
		if(bib == 0) {
			uint8_t CMD24[] = {
				0x58,
				(uint8_t)((block >> 24) & 0xFF),
				(uint8_t)((block >> 16) & 0xFF),
				(uint8_t)((block >> 8) & 0xFF),
				(uint8_t)(block & 0xFF),
				0x00 //CRC8
			};
			uint8_t Answ[6];
			spi_exchange(CMD24, sizeof(CMD24),Answ);
			for(int i = 0; i<6;i++) GR_DEBUG("CMD24 transfer %d: %d\n", i, Answ[i]);
			GR_DEBUG("Start of new packet\n");
			while(1) {
				uint8_t answer = spi_sendbyte(0xFF);
				GR_DEBUG("CMD24 answer %d\n", answer);
				if(answer==0x00) break;
			}
			spi_sendbyte(0xFF);
			spi_sendbyte(~(0x01));
			spi_sendbyte((uint8_t)(*(ptr+i) & 0xFF));
			bib++;
		}
		else {
			if(bib < 511) {
				spi_sendbyte((uint8_t)(*(ptr+i) & 0xFF));
				bib++;
			}
		}
		if(bib == 511) {
			spi_sendbyte((uint8_t)(*(ptr+i) & 0xFF));
			spi_sendbyte(0xFF);
			spi_sendbyte(0xFF);
			GR_DEBUG("It data answer was %d\n",spi_sendbyte(0xFF));
			while(1) {
				uint8_t answer = spi_sendbyte(0xFF);
				GR_DEBUG("%d\n", answer);
				if(answer) break;
			}
			bib = 0;
			block += 512;
		}
	}
}
