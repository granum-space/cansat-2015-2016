/*
 * uart-debug.c
 *
 *  Created on: 07 мая 2016 г.
 */

#include <stdio.h>
#include <avr/io.h>

#include "uart-debug.h"
#include "config.h"


static int myPutChar(char value, FILE * stream) {
	(void)stream; // не используем переменную. Таким образом глушим варнинг о неиспользуемой переменной

#if defined __AVR_ATmega128__ // для атмеги128 используем UART1 (не UART0)
	while ( !(UCSR1A & (1 << UDRE1)) ){}
	UDR1 = value;
#elif defined __AVR_ATmega328P__ // для атмеги328 используем UART0 (так как другого то и нет)
	while ( !(UCSR0A & (1 << UDRE0)) ){}
	UDR0 = value;
#endif
	return 0;
}

// глобальная переменная stdout
FILE mystdout = FDEV_SETUP_STREAM(myPutChar, NULL, _FDEV_SETUP_WRITE);

void initUartDebug() {
#if defined __AVR_ATmega128__ // для атмеги128 используем UART1 (не UART0)
	UCSR1B = (1 << TXEN1); // включаем только TX

	UCSR1C = (1 << UCSZ10) | (1 << UCSZ11) // Размер символа - 8 бит
		| (0 << UPM10) | (0 << UPM11)      // Бит чертности отключен
		| (0 << USBS1) // 1 стоп бит
	;

	UBRR1L = (int)(F_CPU/(16.0*UART_DEBUG_BAUD_RATE)-1) % 0xFF;
	UBRR1H = (int)(F_CPU/(16.0*UART_DEBUG_BAUD_RATE)-1) / 0xFF;

#elif defined __AVR_ATmega328P__
	UCSR0B = (1 << TXEN0); // включаем только TX

	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01) // Размер символа - 8 бит
		| (0 << UPM00) | (0 << UPM01)      // Бит чертности отключен
		| (0 << USBS0) // 1 стоп бит
	;

	UBRR0L = (int)(F_CPU/(16.0*UART_DEBUG_BAUD_RATE)-1) % 0xFF;
	UBRR0H = (int)(F_CPU/(16.0*UART_DEBUG_BAUD_RATE)-1) / 0xFF;
#endif
	stdout = &mystdout;
}
