#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>
#include <spi.h>

void GPS_Init();
uint8_t GPS_Read_Data();
float latitude; /* широта */
float longitude; /* долгота */



#endif /* GPS_H_ */
