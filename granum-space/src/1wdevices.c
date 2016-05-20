/*
 * source.c
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 *      http://aterlux.ru/index.php?page=article&art=1wire
 */

#include "1wdevices.h"
#include "onewire.h"
#include <util/delay.h>
#include "uart-debug.h"


uint16_t get_temperature()
{
	GR_DEBUG("onewire_reset %d\n", OneWireReset());
	OneWireWriteByte(0xCC);
	OneWireWriteByte(0x44);
	//_delay_ms(1000);
	OneWireReset();
	OneWireWriteByte(0xCC);
	OneWireWriteByte(0xBE);

	int str[9];
	for(int i = 0; i<9 ;i++){
		str[i] = OneWireReadByte();
	}
	// место для контрольной суммы

	uint16_t value = str[0] | (str[1] << 8);
	//float t = value / 16.0f;
	//return t;
	return value;
}



