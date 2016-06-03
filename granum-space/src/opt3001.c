/*
 * opt3001.c
 *
 *  Created on: 03 июня 2016 г.
 *      Author: developer
 */

#include <avr/io.h>
#include "opt3001.h"
#include "i2c.c"
#include "i2c.h"


#define OPT3001
	uint16_t config_opt[16];
	OPT_init(){
						// заполняем конфигурацию
		for(uint8_t i = 0; i < 16; i++){
			config_opt[i] << i;
		}

		i2c_write(config_opt, 16);  		// отправлеям конф на запись
	}




	OPT_read(){									// читаем результат
		uint16_t result[16];
		while(1){
			uint8_t CFR  = config_opt[8] // & | OPT3001 ;
			if(CFR){
				int i2c_read(result, 16);
				break;
			}
		}
			// break;
	}
