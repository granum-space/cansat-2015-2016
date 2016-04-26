/*
 * sd.h
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: developer
 */

#ifndef SD_H_
#define SD_H_
#include <stdint.h>
void sd_init();
uint8_t sd_send_r1cmd(uint8_t cmd, uint32_t arg, uint8_t crc);


#endif /* SD_H_ */
