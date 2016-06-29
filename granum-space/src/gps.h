#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>

extern float latitude, longtitude, height;
extern enum {
	N = 0,
	S = 1
}lat_side;
extern enum {
	E = 0,
	W = 1
}long_side;

void GPS_Init();
uint8_t GPS_update(int cycles);

#endif /* GPS_H_ */
