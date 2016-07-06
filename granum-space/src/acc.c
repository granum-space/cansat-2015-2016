/*
 * acc.c
 *
 *  Created on: 19 марта 2016 г.
 *      Author: developer
 */

#include <util/delay.h>
#include <stdbool.h>

#include "config.h"
#include "i2c.h"
#include "uart-debug.h"

bool acc_needinit = true;

void acc_writereg(uint8_t registry, const void * data_ptr, size_t data_size);
void acc_readreg(uint8_t registry, void * data_ptr, size_t data_size);

void acc_init() {
	if(acc_needinit){
		i2c_init();
		_delay_ms(100);
		uint8_t datarate = DATARATE;
		acc_writereg(BW_RATE, &datarate, 1);
		uint8_t fifoset = FIFOSET;
		acc_writereg(FIFO_CTL, &fifoset, 1);
		uint8_t dataformat = (1<<3)|(1<<1)|(1<<0);
		acc_writereg(DATA_FORMAT, &dataformat, 1);
		uint8_t devid = 0;
		acc_readreg(DEVID,&devid,1);
		GR_DEBUG("DevID = %d\n", devid);
		uint8_t powerctl = POWERCTL;
		acc_writereg(POWER_CTL, &powerctl, 1);
		acc_needinit = false;
	}
}

uint8_t acc_read(int16_t * datax,int16_t * datay,int16_t * dataz) {
	uint8_t fifosize = 0;
	acc_readreg(FIFO_STATUS, &fifosize, 1);
	fifosize &= ~((1<<7)|(1<<6));
	fifosize++;
	uint8_t databuf[6];
	for(int i = 0;i<fifosize;i++) {
		acc_readreg(DATAX0, databuf, 6);
		//GR_DEBUG("%d,%d,%d,%d,%d,%d\n",databuf[0],databuf[1],databuf[2],databuf[3],databuf[4],databuf[5]);
		*(datax+i) = databuf[0]|(databuf[1]<<8);
		*(datay+i) = databuf[2]|(databuf[3]<<8);
		*(dataz+i) = databuf[4]|(databuf[5]<<8);
	}
	if(fifosize==1){
		if(*datax==0){
			fifosize=0;
		}
	}
	return fifosize;
}

void acc_writereg(uint8_t registry, const void * data_ptr, size_t data_size) {
	i2c_reset();
	/*GR_DEBUG("Write start status %d\n",i2c_start());
	GR_DEBUG("Write snd slaw status %d\n",i2c_send_slaw(ACC_ADRESS, false));*/
	i2c_start();
	i2c_send_slaw(ACC_ADRESS, false);
	i2c_write(&registry, 1);
	//GR_DEBUG("Write status %d\n",i2c_write(data_ptr, data_size));
	i2c_write(data_ptr, data_size);
	i2c_stop();
}

void acc_readreg(uint8_t registry, void * data_ptr, size_t data_size) {
	i2c_reset();
	/*GR_DEBUG("Read start status %d\n",i2c_start());
	GR_DEBUG("Read snd slaw status %d\n",i2c_send_slaw(ACC_ADRESS, false));*/
	i2c_start();
	GR_DEBUG("SND slaw error %d\n",i2c_send_slaw(ACC_ADRESS, false));
	i2c_write(&registry, 1);
	i2c_start();
	/*GR_DEBUG("Read snd slaw status %d\n",i2c_send_slaw(ACC_ADRESS, true));
	GR_DEBUG("Read status %d\n",i2c_read(data_ptr, data_size, true));*/
	i2c_send_slaw(ACC_ADRESS, true);
	i2c_read(data_ptr, data_size, true);
	i2c_stop();
}
