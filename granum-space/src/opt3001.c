/*
 * opt3001.c

 *
 *  Created on: 03 июня 2016 г.
 *      Author: developer
 */

#include <util/delay.h>
#include <avr/io.h>
#include "opt3001.h"
#include "i2c.h"

#define OPT3001_ADDR 0x10  // АДРЕСС ДАТЧИКА
#define ADDR_REG 01 // адрес регистра в котором лежит конфигурация в hex
#define ADDR_RES 00 //адрес регистра из которого мы хотим прочитать результат в hex


uint8_t config_opt[16] = {


};
uint16_t result;

int OPT_read(uint8_t ADDR_read){

	int flag = 0;
	flag = i2c_start();
	if(flag != 0)
		return flag;
	flag = i2c_send_slaw(OPT3001_ADDR, false);
	if(flag != 0){
		i2c_stop();
		return flag;
	}
	uint8_t target_register_addr = ADDR_read;
	flag = i2c_write(&target_register_addr, 1);
	if(flag != 0 ){
		i2c_stop();
		return flag;
	}
	i2c_start();
	flag = i2c_send_slaw(OPT3001_ADDR, true);
	    if (flag != 0){
	        i2c_stop();
	        return flag;
	    }
	 if(ADDR_read == ADDR_REG){
		 flag = i2c_read(config_opt, 2, true);
		 if (flag != 0) {
	        i2c_stop();
	        return flag;
		 	 }
		 i2c_stop();
		 return flag;
	 }
	 else{
		 flag = i2c_read(&result, 2, true);
	 	 if (flag != 0) {
	 		 i2c_stop();
	 	     return flag;
	 	 }
	 	 i2c_stop();
	 	 return flag;
	 }
}

uint16_t OPT_RESULT(){
	uint8_t res = ADDR_RES;
	OPT_read(res);
	return result;
}

int OPT_write(uint8_t ADDR_write){
	int flag = 0;
	flag = i2c_start();
	if(flag != 0)
		return flag;
	flag = i2c_send_slaw(OPT3001_ADDR, false);
	if(flag != 0){
		i2c_stop();
		return flag;
	}
	uint8_t target_register_addr = ADDR_write;
	flag = i2c_write(&target_register_addr, 1);
	if (flag != 0)
	{
		i2c_stop();
	    return flag;
	}
	if(ADDR_write == ADDR_REG) {
		flag = i2c_write(config_opt, 2);
	}
	i2c_stop();
	return flag;
}

void OPT_init(){

	OPT_read(ADDR_REG);

	// меняем конфигурацию
	uint8_t uno = ADDR_REG;
	OPT_write(uno);  // отправлеям новую конфу на запись
}

uint8_t OPT_start(){
	while(1){
		OPT_read(ADDR_REG);
		if(config_opt[6] == 1)
			break;
	}
	return 1;
}



