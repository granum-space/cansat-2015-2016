/*
 * opt3001.c

 *
 *  Created on: 03 июня 2016 г.
 *      Author: developer
 */

#include <util/delay.h>
#include <avr/io.h>
#include "opt3001.h"
#include "i2c.c"
#include "i2c.h"

// #define ONE 0000000100000000


	uint16_t config_opt[16];



	OPT_init(){
	for(uint8_t i = 0; i < 16; i++){  //заполняем конфигурацию
			config_opt[i] << i;
		}
		i2c_write(config_opt, 16);  		// отправлеям конф на запись
	}

	OPT_start(){
			while(1){
			if(config_opt[10] == 0) // config_opt[10] флаг выхода за нижнийй лимит если он == 0 то мы вышли из ракеты
				break;
			}
			return 1;
		}



	OPT_read(){									// читаем результат
		uint16_t result[16];
		uint8_t finish = 0; // индикатор ошибки
		while(1){
			uint8_t OVF  = config_opt[7]; // &  (ONE << 1) ;
			uint8_t CRF = config_opt[8]; // & ONE;
			if(CRF == 1 && OVF == 0){	// если преоб-ние завершилось (CRF == 1 ) и если не произошло переполнения (OVF ==0)
					i2c_read(result, 16);
					finish = 1;
			}
			     }

		return finish;
		}


