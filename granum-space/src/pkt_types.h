/*
 * pkt_types.h
 *
 *  Created on: 29 марта 2016 г.
 *      Author: developer
 */

#ifndef PKT_TYPES_H_
#define PKT_TYPES_H_
typedef struct {
	uint16_t beacon; //must be 0xFFFF or 65535
	uint16_t number;
	uint16_t time, time_part;
	uint16_t temperature1;
	int16_t temperature2;
	uint16_t pressure,
		humidity,
		O2, CO2,
		lum,
		term;
	uint8_t legs, seeds;
	uint16_t cntrl;
} dtpkt_t;

typedef struct {
	uint16_t beacon; //must be 0xACCC
	uint16_t number;
	uint16_t time, time_part;
	uint8_t entries;
	int16_t datax[33],datay[33],dataz[33];
	uint16_t cntrl;
} accpkt_t;


#endif /* PKT_TYPES_H_ */
