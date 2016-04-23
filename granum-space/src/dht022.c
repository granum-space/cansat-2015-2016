#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "onewire.h"

#define DHT_PORT PORTC
#define DHT_PPIN PINC
#define DHT_DDR DDRC
#define DHT_PIN 0

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
	if (DHT_PPIN & (1 << DHT_PIN) != 0)
		return 1;
	else
		return 0;
}



// начало связи с dht
// если все хорошо возвращает ноль
// если устроиство не отвечает то возвращает 1
// если линия не поднялась возвращает 2
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
		return 1;

	for (int i = 0; i < 120; i++)
	{
		if(DHT_ReadBus() != 0 )
			return 0;
	}

	return 2;
}

int DHT_wait_start(){

	int value = 0;

	for(int i = 0; i < 100; i++){
		if(DHT_ReadBus() == 0){
			value = 1;
			break;
		}
		_delay_us(1);
	}

	if(value) return 1;
	return 0;
}


// если возвращет -1 то передача не началась
// если возвращает -2 то передача не кончилась
int DHT_read_bit()
{
	bool bitStarted = false;
	for (int i = 0; i < 50; i++)
	{
		_delay_us(1);
		if (DHT_ReadBus() != 0)
		{
			bitStarted = true;
			break;
		}
	}

	if (!bitStarted) return -1;

	bitStarted = false;
	int i;
	for (i = 0; i < 100; i++){
		_delay_us(1);
		if (DHT_ReadBus() == 0)
		{
			bitStarted = true;
			break;
		}
	}

	if (!bitStarted)
		return -2;

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
	for(int i = 1, j = 6; i < 9, j > -1;i++ , j--){
		retval = retval | num[i] << j;
	}

	return retval;
}


int DHT_Read(uint16_t * humidity, uint16_t * temp)
{
	DHT_wait_start();
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

	return 0;
}
