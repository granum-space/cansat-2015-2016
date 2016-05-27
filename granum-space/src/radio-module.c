


#include "radio-module.h"
#include <avr/io.h>
#include <util/delay.h>

#include "config.h"


void radio_write(const uint8_t *value, size_t size){

	for(size_t i = 0; i < size; i++){
		while(((CTSPIN << CTSLEG) & CTSPIN )  != 0)
		{}
		while ( !(UCSR0A & (1 << UDRE0)) )
		{}
		UDR0 = *(value+i);
	}
}


void radio_init(){

	CFGDDR = CFGDDR | (1 << CFGLEG);
	CTSDDR = CTSDDR & ~(1 << CTSLEG);

	// инициализация уарт
	UCSR0B = (1 << TXEN0) | (1 << RXC0);// включаем только TX

	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01) // Размер символа - 8 бит
		| (0 << UPM00) | (0 << UPM01)      // Бит четности отключен
		| (0 << USBS0) // 1 стоп бит
	;

	UBRR0L = (int)(F_CPU/(16.0*RXQ2_BAUD_RATE)-1) % 0xFF;
	UBRR0H = (int)(F_CPU/(16.0*RXQ2_BAUD_RATE)-1) / 0xFF;

	CFGPORT = CFGPORT | (1 << CFGLEG);
	uint8_t test = 100;
	radio_write(&test , 1);
	_delay_ms(100);
	CFGPORT &= ~(1 << CFGPORT);

	uint8_t config[12] = {
		RF_TARGET_ADDR,
		RF_SELF_ADDR,
		RF_CH,
		RF_POWER,
		RF_TX_PACKET,
		RF_RX_PACKET,
	};

	radio_write(config, 1);
	_delay_ms(1000);
	radio_write(config, 12);
	_delay_ms(1000);
	CFGPORT = CFGPORT | (1 << CFGLEG);
}
