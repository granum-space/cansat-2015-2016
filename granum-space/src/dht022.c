#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

#include "onewire.h"
#include "dht022.h"

#define DHT_PORT PORTC	// Регистр PORT порта, на котором подсоединен датчик DHT022
#define DHT_PPIN PINC	// Регистр PIN порта на котором подсоединен датчик DHT022
#define DHT_DDR DDRC	// Регистр ВВК порта на котором подсоединен датчик DHT022
#define DHT_PIN 1		// Номер пина в порту


void DHT_Init()
{
	DHT_PORT &= ~(1 << DHT_PIN);
	DHT_DDR &= ~(1 << DHT_PIN);
}


void DHT_SetBusZero()
{
	DHT_DDR |= (1 << DHT_PIN);
}


void DHT_SetBusOne()
{
	DHT_DDR &= ~(1 << DHT_PIN);
}


int DHT_ReadBus()
{
	if ((DHT_PPIN & (1 << DHT_PIN)) != 0)
		return 1;
	else
		return 0;
}


// начало связи с dht
// если все хорошо возвращает ноль
// если устроиство не отвечает то возвращает -1 * DHT_ERROR_NO_REPLY
// если линия не поднялась после ответа за заданное время возвращает -1 * DHT_ERROR_REPLY_TOO_LONG
int DHT_Reset()
{
	DHT_SetBusZero();
	_delay_us(20);
	DHT_SetBusOne();
	_delay_us(40);

 	bool isSomeoneHere = false;
	for (int i = 0; i < 40; i++)
	{
		if (DHT_ReadBus() == 0)
		{
			isSomeoneHere = true;
			break;
		}

		_delay_us(1);
	}

	if (!isSomeoneHere)
		return DHT_ERROR_NO_REPLY;

	for (int i = 0; i < 120; i++)
	{
		if(DHT_ReadBus() != 0 )
			return 0;
	}

	return DHT_ERROR_REPLY_TOO_LONG;
}


int DHT_wait_bit_start(){

	int value = 0;

	for(int i = 0; i < 100; i++){
		if(DHT_ReadBus() == 0){
			value = 1;
			break;
		}
		_delay_us(1);
	}

	if(!value) return DHT_ERROR_WAIT_TO_LONG;
	return 0;
}


// если значение отрицательное, то это код ошибки:
// 		DHT_ERROR_WAIT_TO_LONG -> передача бита не началась
// 		DHT_ERROR_BIT_TO_LONG -> передача бита не кончилась
// из положительных значений возвращает 0 или 1
int DHT_read_bit()
{
	bool bitStartedOrEnded = false;
	for (int i = 0; i < 50; i++)
	{
		_delay_us(1);
		if (DHT_ReadBus() != 0)
		{
			bitStartedOrEnded = true;
			break;
		}
	}

	if (!bitStartedOrEnded) return DHT_ERROR_WAIT_TO_LONG;

	bitStartedOrEnded = false;
	int i;
	for (i = 0; i < 100; i++){
		_delay_us(1);
		if (DHT_ReadBus() == 0)
		{
			bitStartedOrEnded = true;
			break;
		}
	}

	if (!bitStartedOrEnded)
		return DHT_ERROR_BIT_TO_LONG;

	if(i > 50) return 1;
	else return 0;
}


int DHT_read_byte(){
	int num[8];
	for(int i = 0; i < 8; i++){
		int value = DHT_read_bit();
		if (value < 0)
			return value;

		num[i] = value;
	}

	uint8_t retval = 0;
	retval = num[0] << 7;

	// FIXME: Этот цикл нужно внимательно проверить
	// выражение i < 9, j > -1 не имеет смысла.
	// и очень странным выглядит j = 6, j-- и i < 9. Похоже что j пойдет в отрицательные значения
	for(int i = 1, j = 6; i < 9, j > -1;i++ , j--){
		retval = retval | num[i] << j;
	}

	return retval;
}


int DHT_Read(uint16_t * humidity, int16_t * temp)
{
	int wait_start_status = DHT_wait_bit_start();
	if (wait_start_status < 0)
		return wait_start_status;

	int sum[5];
	for( int i = 0; i<5; i++){
		sum[i] = DHT_read_byte();
		if (sum[i] < 0)
			return sum[i];
	}

	if (sum[0] + sum[1] + sum[2] + sum[3] != sum[4])
		return -10;


	*humidity = (sum[0] << 8) | sum[1];
	*temp = (sum[2] << 8) | sum[3];
	// FIXME: Температура может быть отрицательной.
	// Нужно проверить правильно ли побитовый сдвиг отработает в этой ситуации

	return 0;
}
