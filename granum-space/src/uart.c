/*
 * uart.c
 *
 *  Created on: 05 марта 2016 г.
 *      Author: developer
 */
#include <avr/io.h>

#define TARGET_BAUD_RATE 9600

void uart_send(uint8_t value) {
	/*#if defined __AVR_ATmega128__ // для атмеги128 используем UART1 (не UART0)
		while ( !(UCSR1A & (1 << UDRE1)) ){}
		UDR1 = value;
	#elif defined __AVR_ATmega328P__*/ // для атмеги328 используем UART0 (так как другого то и нет)
		while ( !(UCSR0A & (1 << UDRE0)) ){}
		UDR0 = value;
	//#endif
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
	while ( !(UCSR0A & (1 << RXC0)) ){}

	return UDR0;
	}


void uart_read_many(const void* ptr, int length) {
	uint8_t * ptr2 = (uint8_t*) ptr;
	for(int i = 0; i<length; i++) {
		*ptr2 = uart_receive();
		ptr2++;
	}
}

/*int uart_receive()
	{
	while ( !(UCSR0A & (1 << RXC0)) )
	{}

	return UDR0;
	}*/

void uart_init() {
	/*#if defined __AVR_ATmega128__ // для атмеги128 используем UART1 (не UART0)
		UCSR0B = (1 << TXEN0); // включаем только TX

		UCSR0C = (1 << UCSZ00) | (1 << UCSZ01) // Размер символа - 8 бит
			| (0 << UPM00) | (0 << UPM01)      // Бит чертности отключен
			| (0 << USBS0) // 1 стоп бит
		;

		UBRR1L = (int)(F_CPU/(16.0*TARGET_BAUD_RATE)-1) % 0xFF;
		UBRR1H = (int)(F_CPU/(16.0*TARGET_BAUD_RATE)-1) / 0xFF;

	#elif defined __AVR_ATmega328P__*/
		UCSR0B = (1 << TXEN0); // включаем только TX

		UCSR0C = (1 << UCSZ00) | (1 << UCSZ01) // Размер символа - 8 бит
			| (0 << UPM00) | (0 << UPM01)      // Бит чертности отключен
			| (0 << USBS0) // 1 стоп бит
		;

		UBRR0L = (int)(F_CPU/(16.0*TARGET_BAUD_RATE)-1) % 0xFF;
		UBRR0H = (int)(F_CPU/(16.0*TARGET_BAUD_RATE)-1) / 0xFF;
	//#endif
}
