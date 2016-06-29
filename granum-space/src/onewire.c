#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdbool.h>

#include "config.h"
#include "onewire.h"

bool OneWireNeedinit = true;

void OneWireInit()
{
	if(OneWireNeedinit){
		ONE_WIRE_PORT &= ~(1 << ONE_WIRE_PIN);
		ONE_WIRE_DDR &= ~(1 << ONE_WIRE_PIN);
		OneWireNeedinit = false;
	}
}

void OneWireSetBusZero()
{
	ONE_WIRE_DDR |= (1 << ONE_WIRE_PIN);
}

void OneWireSetBusOne()
{
	ONE_WIRE_DDR &= ~(1 << ONE_WIRE_PIN);
}

int OneWireReadBus()
{
	if ((ONE_WIRE_PPIN & (1 << ONE_WIRE_PIN)) != 0)
		return 1;
	else
		return 0;
}

int OneWireReset()
{
	OneWireSetBusZero();
	_delay_us(600);
	OneWireSetBusOne();
	_delay_us(10);

	int isSomeoneHere = 0;
	for (int i = 0; i < 480; i++)
	{
		if (OneWireReadBus() == 0)
			isSomeoneHere = 1;

		_delay_us(1);
	}

	return isSomeoneHere;
}

void OneWireWriteBit(int value)
{
	OneWireSetBusZero();
	_delay_us(2);
	if (value != 0)
	{
		OneWireSetBusOne();
	}

	_delay_us(60);
	OneWireSetBusOne();
}

void OneWireWriteByte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t bit = (1<<i) &byte;
		OneWireWriteBit(bit);
	}
}

int OneWireReadBit ()
{
	OneWireSetBusZero();
	_delay_us (2);
	OneWireSetBusOne();
	_delay_us (20);
	int x = OneWireReadBus();
	_delay_us(30);
	return x;
}

uint8_t OneWireReadByte ()
{
	uint8_t retval = 0;
	for (uint8_t i = 0; i < 8; i++)
	{
		uint8_t bit = OneWireReadBit();
		retval = retval | (bit<<i);
	}
	return retval;
}


void OneWireWriteBytes(const void * ptr, size_t size)
{
	const uint8_t * casted_ptr = (const uint8_t*)ptr;
	for (size_t i = 0; i < size; i++)
	{
		OneWireWriteByte(*(casted_ptr + i));
	}
}


void OneWireReadBytes(void * ptr, size_t size)
{
	uint8_t * casted_ptr = (uint8_t*)ptr;
	for (size_t i = 0; i < size; i++)
	{
		*(casted_ptr + i) = OneWireReadByte();
	}
}







