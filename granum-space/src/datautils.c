

#include "spi.h"
#include "sd.h"

uint32_t block = 0;
uint16_t bib = 0;

uint8_t du_init() {
	sd_init();
	return 0;
}

void du_write(const void* data, int length) {
	uint8_t* ptr = (uint8_t*) data;
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
			spi_exchange(CMD24, sizeof(CMD24),0);
			while(1) {
					if(!spi_sendbyte(0xFF)) break;
			}
			spi_sendbyte(0xFF);
			spi_sendbyte(~(1));
			spi_sendbyte((uint8_t)(*(ptr+i) & 0xFF));
			bib++;
		}
		else {
			if(bib < 511) {
				spi_sendbyte((uint8_t)(*(ptr+i) & 0xFF));
				bib++;
			}
		}
		if(bib == 512) {
			spi_sendbyte((uint8_t)(*(ptr+i) & 0xFF));
			spi_sendbyte(0xFF);
			spi_sendbyte(0xFF);
			spi_sendbyte(0xFF);
			while(1) {
				if(!spi_sendbyte(0xFF)) break;
			}
			bib = 0;
			block++;
		}
	}
}
