/*
 * onewire.h
 *
 *  Created on: 27 февр. 2016 г.
 *      Author: developer
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include <stdint.h>
#include <stddef.h>

void OneWireInit();

int OneWireReset();

void OneWireWriteByte(uint8_t byte);
void OneWireWriteBytes(const void * ptr, size_t size);

uint8_t OneWireReadByte();
void OneWireReadBytes(void * ptr, size_t size);





#endif /* ONEWIRE_H_ */

