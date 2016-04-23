/*
 * dht022.h
 *
 *  Created on: 23 апр. 2016 г.
 *      Author: developer
 */

#ifndef DHT022_H_
#define DHT022_H_

void DHT_Init();

int DHT_Read(uint16_t * humidity, uint16_t * temp);


#endif /* DHT022_H_ */
