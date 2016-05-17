/*
 * uart.c
 *
 *  Created on: 05 марта 2016 г.
 *      Author: developer
 */
#include <avr/io.h>

void uart_send(uint8_t value)
	{
	while ( !(UCSR0A & (1 << UDRE0)) )
	{}

	UDR0 = value;
	}

void uart_send_many(const void* ptr, int length){
	uint8_t * ptr2 = (uint8_t*) ptr;
	for(int i = 0; i<length; i++) {
		uart_send(*ptr2);
		ptr2++;
	}
}

int uart_receive()
	{
	while ( !(UCSR0A & (1 << RXC0)) )
	{}

	return UDR0;
	}

void uart_init()
	{
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // включаем TX RX
		;
		UCSR0C = (1 << UCSZ00) | (1 << UCSZ01) // Размер символа - 8 бит
			| (0 << UPM00) | (0 << UPM01)      // Бит чертности отключен
			| (0 << USBS0) // 1 стоп бит
		;
		//те в 16мг
		// baud на 9600 по таблице на частоте в 16мгц
		UBRR0H = 51 / 0xFF;
		UBRR0L = 51 % 0xFF;
	}
