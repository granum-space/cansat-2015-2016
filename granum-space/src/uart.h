/*
 * uart.h
 *
 *  Created on: 05 марта 2016 г.
 *      Author: developer
 */

#ifndef UART_H_
#define UART_H_

void uart_send(uint8_t value);
int uart_receive();
void uart_init();
void uart_send_many(const void* ptr, int length);

#endif /* UART_H_ */
