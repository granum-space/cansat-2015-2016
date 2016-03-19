/*
 * humidity.h
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#ifndef HUMIDITY_H_
#define HUMIDITY_H_

#include <stdint.h>

typedef struct
{
	uint16_t humidity;
	uint16_t temperature;
} HTData;

HTData ow_getHTData ();
uint16_t Temper()
{
	OneWireReset();
	OneWireWriteByte(0xCC);
	OneWireWriteByte(0x44);
	_delay_ms(1000);
	OneWireReset();
	OneWireWriteByte(0xCC);
	OneWireWriteByte(0xBE);
	int str[9];
	for(int i = 0; i<9 ;i++){
		str[i] = OneWireReadByte();
}

	#endif /* HUMIDITY_H_ */


