#include <avr/io.h>

#define SPIDDR DDRB
#define SPIPORT PORTB
#define MOSI 2
#define MISO 3
#define SCLK 1
#define SS 0

void spi_init()
	{
	SPIDDR |= (1<<MOSI)|(1<<SS)|(1<<SCLK);
	SPIPORT |= (1<<MOSI)|(1<<SS)|(1<<SCLK)|(1<<MISO);
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
	}

uint8_t spi_sendbyte(uint8_t arg) {
	SPIPORT &= ~(1<<SS);
	SPDR = arg;
	while(!(SPSR & (1<<SPIF)));
	SPIPORT |= (1<<SS);
	return SPDR;
}
