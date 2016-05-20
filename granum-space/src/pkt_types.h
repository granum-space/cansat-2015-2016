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
	uint16_t temperature1, temperature2,
		pressure,
		humidity,
		O2, CO2,
		rezistance12, rezistance23, rezistance13;
	uint8_t legs, parachute;
	uint16_t cntrl;
} dtpkt_t;


#endif /* PKT_TYPES_H_ */
