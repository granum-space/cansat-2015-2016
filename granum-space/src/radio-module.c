


#include "radio-module.h"
#include <avr/io.h>

#define CFGDDR DDRA
#define CFGLEG 6
#define CFGPORT PORTA

#define TARGET_BAUD_RATE 9600

#define RFCH 107 // частота канала передачи при добавлении 1 и увеличивается на 100kHz
#define TxPower 3
#define RxPacket 30 // размер принимаемых  пакетов
#define TxPacket 30 // размер отсылаемых пакетов

#define CTSDDR DDRA
#define CTSPIN PINA
#define CTSLEG 4


void radio_write(const char *value, size_t size){

	for(size_t i = 0; i < size; i++){
		while(((CTSPIN << CTSLEG) & CTSPIN )  != 0)
		{}
		while ( !(UCSR1A & (1 << UDRE1)) )
		{}
		UDR1 = *(value+i);
	}
}


void radio_init(){

	CFGDDR = CFGDDR | (1 << CFGLEG);
	CTSDDR = CTSDDR & ~(1 << CTSLEG);

	// инициализация уарт
	UCSR0B = (1 << TXEN0) | (1 << RXC0);// включаем только TX

	UCSR0C = (1 << UCSZ00) | (1 << UCSZ00) // Размер символа - 8 бит
		| (0 << UPM00) | (0 << UPM00)      // Бит четности отключен
		| (0 << USBS0) // 1 стоп бит
	;

	UBRR0L = (int)(F_CPU/(16.0*TARGET_BAUD_RATE)-1) % 0xFF;
	UBRR0H = (int)(F_CPU/(16.0*TARGET_BAUD_RATE)-1) / 0xFF;

	CFGPORT = CFGPORT | (1 << CFGLEG);
	uint8_t test = 100;
	radio_write(&test , 1);
	_delay_ms(100);
	CFGPORT &= ~(1 << CFGPORT);

	uint8_t config[12] = {
			0x4a, 0x4b, 0x4c, 0x4d, // Адрес, на который модуль будет отправлять данные
			0x5a, 0x5b, 0x5c, 0x5d, // Адрес, данные для которого модуль будет получать
			RFCH,        // Номер радиокала (частота)
			TxPower,          // Мощность радиопередатчика. Значения 0: -10dBm, 1: -2dBm, 2: +6dBm, 3: +10dBm
			TxPacket,       // Размер передаваемых пакета (не более 0x1f)
			RxPacket,       // Размер принимаемых пакетов (не более 0x1f)
	};

	radio_write( config , 1);
	_delay_ms(10*12*1000/TARGET_BAUD_RATE*2);
	radio_write(config , 12);
	CFGPORT = CFGPORT | (1 << CFGLEG);
}
