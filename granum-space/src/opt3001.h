/*
 * opt3001.h
 *
 *  Created on: 03 июня 2016 г.
 *      Author: developer
 */

#ifndef OPT3001_H_
#define OPT3001_H_

#include <util/delay.h>
#include <avr/io.h>



// инициализация
void OPT_init();

// возвращает 1 если мы вышли из ракеты и 0 если еще нет
uint8_t OPT_start();

// возвращает результат измерения
uint16_t OPT_RESULT();

#endif /* OPT3001_H_ */
