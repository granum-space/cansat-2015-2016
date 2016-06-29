/*
 * Time.h
 *
 *  Created on: 12 марта 2016 г.
 *      Author: developer
 */

#ifndef TIME_H_
#define TIME_H_
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint16_t seconds;
	uint16_t subseconds;
} timeData_t ;


void TimeServiceInit ();
timeData_t TimeServiceGet ();
timeData_t TimeSum (timeData_t aa, timeData_t b);
bool Compare (timeData_t aa, timeData_t bb);
timeData_t Txnach (timeData_t Tx);
timeData_t Txplus (timeData_t Tx);



#endif /* TIME_H_ */
