

#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>

#include "config.h"
#include "spi.h"
#include "sd.h"
#include "uart-debug.h"
#include "radio-module.h"

bool du_needinit = true;

uint32_t block = 0;
uint16_t bib = 0;


void du_init() {
	if(du_needinit){
		radio_init();
		GR_DEBUG("Radio init completed!");

		for(int i=0;i<10;i++) {
			//GR_DEBUG("I'm there99\n");
			if(sd_init()==0x00) {
				//GR_DEBUG("I'm there66\n");
				break;
			}
			_delay_ms(100);
		} //Для SD карты
		du_needinit = false;
	}
}

void du_write(const void* data, int length) {
	radio_write(data, length);
	const uint8_t* ptr = (const uint8_t*) data;
	for(int i = 0; i < length; i++) {
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
			//for(int i = 0; i<6;i++) GR_DEBUG("CMD24 transfer %d: %d\n", i, Answ[i]);
			//GR_DEBUG("Start of new packet\n");
			for(int i=0;i<10;i++) {
				uint8_t answer = spi_sendbyte(0xFF);
				//GR_DEBUG("CMD24 answer %d\n", answer);
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
			spi_sendbyte(*(ptr+i));
			spi_sendbyte(0x99);
			spi_sendbyte(0x99);
			//GR_DEBUG("It data answer was %d\n",spi_sendbyte(0xFF));
			for(int ii=0;ii<10;ii++) {
				uint8_t answer = spi_sendbyte(0xFF);
				//GR_DEBUG("%d\n", answer);
				if(answer) break;
			}
			bib = 0;
			block += 512;
		}
	} //Для SD карты
}
