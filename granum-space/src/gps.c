/*
 * gps.c
 *
 *  Created on: 23 мая 2016 г.
 *      Author: developer
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>

#include "spi.h"
#include "config.h"

bool gps_needinit = true;

enum {
	SEARCHING,
	WAITING_GP,
	WAITING_MES_T,
	COLLECTING_GGA,
	COLLECTING_GLL,
	COLLECTING_RMC

} gps_status;

char gps_buffer[100];
uint8_t gps_index = 0;

float latitude = 0.0f, longtitude = 0.0f, height = 0.0f;
char lat_side,long_side;

void GPS_Init()
{
	if(gps_needinit){
		SPI_DDRX |= (1<<GPSSS);
		spi_init();
		gps_status = SEARCHING;
		gps_needinit = false;
	}
}

void parse_GGA();
void parse_GLL();
void parse_RMC();

bool GPS_update(int cycles)
{
	SPI_PORTX |= (1<<GPSSS);
	bool updated;
	char symbol;
	int i=0;
	for(i = 0;i<cycles;i++)
	{
		symbol = (char)spi_sendbyte(0xFF);
		//printf("%c\n", symbol);
		//printf("symbol=%c (%x)\n", symbol, (unsigned char)symbol);
		switch(gps_status){
		case SEARCHING:
			if(symbol == '$') {
				gps_buffer[gps_index] = symbol;
				gps_index++;
				gps_status = WAITING_GP;
			}
			break;
		case WAITING_GP:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(gps_index==3) {
				if(gps_buffer[1] == 'G' && gps_buffer[2] == 'P') {
					gps_status = WAITING_MES_T;
				}
				else {
					gps_status = SEARCHING;
					gps_index = 0;
				}
			}
			break;
		case WAITING_MES_T:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(gps_index==6) {
				if(gps_buffer[3] == 'G') {
					if(gps_buffer[4] == 'G') {
						if(gps_buffer[5] == 'A') {
							printf("GGA found\n");
							gps_status = COLLECTING_GGA;
						}
						else {
							gps_status = SEARCHING;
							gps_index = 0;
						}
					}
					else {
						if(gps_buffer[4] == 'L' && gps_buffer[5] == 'L') {
								printf("GLL found\n");
								gps_status = COLLECTING_GLL;
						}
						else {
							gps_status = SEARCHING;
							gps_index = 0;
						}
					}
				}
				else {
					if(gps_buffer[3] == 'R' && gps_buffer[4] == 'M' && gps_buffer[5] == 'C') {
						printf("RMC found\n");
						gps_status = COLLECTING_RMC;
					}
					else {
						gps_status = SEARCHING;
						gps_index = 0;
					}
				}
			}
			break;
		case COLLECTING_GGA:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(symbol == '\n') {
				gps_index--;
				printf("End of GGA packet.\n");
				parse_GGA();
				gps_index = 0;
				gps_status = SEARCHING;
				updated = true;
			}
			break;
		case COLLECTING_GLL:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(symbol == '\n') {
				gps_index--;
				printf("End of GLL packet.\n");
				parse_GLL();
				gps_index = 0;
				gps_status = SEARCHING;
				updated = true;
			}
			break;
		case COLLECTING_RMC:
			gps_buffer[gps_index] = symbol;
			gps_index++;
			if(symbol == '\n') {
				printf("End of RMC packet.\n");
				parse_RMC();
				gps_index = 0;
				gps_status = SEARCHING;
				updated = true;
			}
			break;
		}
	}
	SPI_PORTX &= ~(1<<GPSSS);
	return updated;
}

void parse_GGA() {
	uint8_t block[15];
	uint8_t block_index = 1;
	for(int i = 0;i<gps_index;i++) {
		if(gps_buffer[i] == ',') {
			block[block_index] = (i+1);
			block_index++;
		}
	}
	latitude = atof(&gps_buffer[block[2]]);
	lat_side = gps_buffer[block[3]];
	longtitude = atof(&gps_buffer[block[4]]);
	long_side = gps_buffer[block[5]];
	height = atof(&gps_buffer[block[9]]);
	printf("%c%f %c%f %f meters\n",lat_side, latitude,long_side, longtitude, height);
}

void parse_GLL() {
	uint8_t block[8];
	uint8_t block_index = 1;
	for(int i = 0;i<gps_index;i++) {
		if(gps_buffer[i] == ',') {
			block[block_index] = (i+1);
			block_index++;
		}
	}
	if(gps_buffer[block[6]]=='A'){
		latitude = atof(&gps_buffer[block[1]]);
		lat_side = gps_buffer[block[2]];
		longtitude = atof(&gps_buffer[block[3]]);
		long_side = gps_buffer[block[4]];
		printf("%c%f %c%f %f meters\n",lat_side, latitude,long_side, longtitude, height);
	}
}

void parse_RMC() {
	uint8_t block[12];
	uint8_t block_index = 1;
	for(int i = 0;i<gps_index;i++) {
		if(gps_buffer[i] == ',') {
			block[block_index] = (i+1);
			block_index++;
		}
	}
	if(gps_buffer[block[2]]=='A'){
		latitude = atof(&gps_buffer[block[3]]);
		lat_side = gps_buffer[block[4]];
		longtitude = atof(&gps_buffer[block[5]]);
		long_side = gps_buffer[block[6]];
		printf("%c%f %c%f %f meters\n",lat_side, latitude,long_side, longtitude, height);
	}
}
