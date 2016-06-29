/*
 * Time.c
 *
 *  Created on: 12 марта 2016 г.
 *      Author: developer
 */

#include "time.h"

#include "avr/io.h"
#include "avr/interrupt.h"
#include <stdbool.h>

#include <stdint.h>
#include <util/delay.h>
#include <stdbool.h>

#define MaxSubSeconds 31250

bool TimeServiceNeedinit = true;

volatile uint16_t _seconds = 0;


ISR (TIMER1_COMPA_vect) {
	//PORTG ^= (1<< 3);
	 _seconds++;
}


void TimeServiceInit() {
	if(TimeServiceNeedinit){
		TCCR1A= 0;
		//TCCR1B = (1<< WGM12)|(1<< WGM13);//| (1<< CS12);
		TCCR1B = (1<< WGM12)|(0<< WGM13);//| (1<< CS12);
		//ICR1 = 31250;
		OCR1A = MaxSubSeconds;
		TIMSK = (1<<OCIE1A);
		TCCR1B |= (1<< CS12);
		TimeServiceNeedinit = false;
	}
}

timeData_t TimeServiceGet () {
	timeData_t retval;
	cli();

	retval.subseconds = TCNT1;
	retval.seconds = _seconds ;

	sei();

	return retval;
	}


timeData_t TimeSum (timeData_t aa, timeData_t b) {
	timeData_t summa;
	summa.seconds = aa.seconds + b.seconds;
	summa.subseconds = aa.subseconds + b.subseconds;
	if (summa.subseconds >= MaxSubSeconds) {
		summa.seconds = summa.seconds + 1;
		summa.subseconds = summa.subseconds - MaxSubSeconds;
	}
	return summa;
}


bool Compare (timeData_t aa, timeData_t bb) {
	if (aa.seconds >= bb.seconds && aa.subseconds >= bb.subseconds)
		return true;
		else return false;
}





