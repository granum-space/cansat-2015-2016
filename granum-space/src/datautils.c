

#include <util/delay.h>
#include <avr/io.h>

#include "spi.h"
#include "sd.h"
#include "uart-debug.h"
#include "uart.h"

#define RPORT PORTC
#define RDDR DDRC
#define RCFGNUM 1
#define RRTSNUM 2
#define RCTSNUM 3

uint32_t block = 0;
uint16_t bib = 0;

#define CONFIG RPORT &= ~(1<<RCFGNUM);
#define OPER RPORT |= (1<<RCFGNUM);
#define RTS_EN RPORT &= ~(1<<RRTSNUM);
#define RTS_DIS RPORT |= (1<<RRTSNUM);
#define CTS (RPIN & (1<<RCTSNUM));

void du_init() {
	uart_init();

	/*RDDR |= (1<<RCFGNUM)|(1<<RRTSNUM);
	RDDR &= ~(1<<RCTSNUM);

	OPER
	_delay_us(10);

	CONFIG
	RTS_EN
	uint8_t config[] = {
			0x7E,0x7E,0x7E,0x7E, //destination address
			0x7E,0x7E,0x7E,0x7E //self address
	};
	uart_send_many(config, sizeof(config));
	RTS_DIS
	OPER

	CONFIG
	RTS_EN
	uart_send_many(config, 1);

	uint8_t data_to_verify[11];
	uart_read_many(data_to_verify, sizeof(data_to_verify));
	GR_DEBUG("ggg\n");
	RTS_DIS

	GR_DEBUG("%d %d %d %d %d %d %d %d %d %d %d\n", data_to_verify[0],
													data_to_verify[1],
													data_to_verify[2],
													data_to_verify[3],
													data_to_verify[4],
													data_to_verify[5],
													data_to_verify[6],
													data_to_verify[7],
													data_to_verify[8],
													data_to_verify[9],
													data_to_verify[10]);*/
	/*while(1) {
		if(sd_init()==0x00) {
			break;
		}
		_delay_ms(100);
	}*/
}

void du_write(const void* data, int length) {
	const uint8_t* ptr = (const uint8_t*) data;
	for(int i = 0; i < length; i++) {
		uart_send(*(ptr+i));
		/*if(bib == 0) {
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
		}*/
	}
}
