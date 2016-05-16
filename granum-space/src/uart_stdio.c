/*
 * uart_stdio.c
 *
 *  Created on: 27 февр. 2016 г.
 *      Author: developer
 */
#include <avr/io.h>
#include <stdio.h>

static int myPutChar(char value, FILE * stream) {
	(void)stream; // не используем переменную. Таким образом глушим варнинг о неиспользуемой переменной

	while ( !(UCSR0A & (1 << UDRE0)) )
	{}

	UDR0 = value;
	return 0;
}

static int myGetChar(FILE * stream) {
	(void)stream; // не используем переменную. Таким образом глушим варнинг о неиспользуемой переменной

	while ( !(UCSR0A & (1 << RXC0)) )
	{}

	return UDR0;
}

// глобальная переменная stdout
FILE mystdout = FDEV_SETUP_STREAM(myPutChar, NULL, _FDEV_SETUP_WRITE);
FILE mystdin = FDEV_SETUP_STREAM(NULL, myGetChar, _FDEV_SETUP_READ);

void initUartStdio() {
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

	stdout = &mystdout;
	stdin = &mystdin;
}
