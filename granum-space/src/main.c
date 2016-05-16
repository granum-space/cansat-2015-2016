/*
 * main.c
 *
 *  Created on: 09 апр. 2016 г.
 *      Author: developer
 */

#include <avr/io.h>
#include <util/delay.h>
#include "uart_stdio.h"
#include "datautils.h"
#include "uart-debug.h"
#include "sd.h"
#include "spi.h"
#include "i2c.h"
#include "adc.h"

void spi_test_main()
{
	initUartStdio();
	spi_init();
	_delay_ms(5000);
	du_init();
	uint8_t Bytes[1024];
	DEBUG("Sending bytes\n");
	for(int i = 0;i<1024;i++) {
		Bytes[i]=(uint8_t)(i & 0xFF);
		DEBUG("%d\  ", Bytes[i]);
	}
	du_write(Bytes, 1024);
	//while(1) {
		_delay_ms(100);
		while(1) {
			//DEBUG("It finally answered %d\n", sd_init());
			if(sd_init()==0x00) {
				break;
			}
		}
		uint8_t CMD24[] = {
					0x58,
					0x00,
					0x00,
					0x02,
					0x00,
					0x00 //CRC8
			};
		spi_exchange(CMD24, sizeof(CMD24),0);
		uint8_t answer;
		while(1) {
			answer = spi_sendbyte(0xFF);
			GR_DEBUG("It sayed %d\n", answer);
			if(answer == 0x00) break;
		}
		spi_sendbyte(0xFF);
		GR_DEBUG("Sending data\n");
		spi_sendbyte(~(1));
		for(int i = 0;i<512;i++) {
			spi_sendbyte((uint8_t)/*(i & 0xFF)*/0xFC);
		}
		spi_sendbyte(0xFF);
		spi_sendbyte(0xFF);
		answer = spi_sendbyte(0xFF);
		GR_DEBUG("It told %d\n", answer);
		while(1)spi_sendbyte(0xFF);
	//
}




typedef struct {
	int16_t ac1, ac2, ac3;
	uint16_t ac4, ac5, ac6;
	int16_t b1, b2;
	int16_t mb, mc, md;

} BMP085Calibration;


int bmp085LoadCalibration(BMP085Calibration * cal) {

	const uint8_t calRegAddr = 0xAA;
	int status;
	i2c_reset();

	status = i2c_start();
	if (status != 0) {
		printf("i2cStart1 error %d\r\n", status);
		return status;
	}
	status = i2c_send_slaw(0x77, false);
	if (status != 0) {
		printf("i2cSendSLAW1 error %d\r\n", status);
		return status;
	}
	status = i2c_write(&calRegAddr, 1);
	if (status != 0) {
		printf("i2cWrite error %d\r\n", status);
		return status;
	}


	status = i2c_start();
	if (status != 0) {
		printf("i2cWrite start2 %d\r\n", status);
		return status;
	}
	status = i2c_send_slaw(0x77, true);
	if (status != 0) {
		printf("i2cSendSLAW2 error %d\r\n", status);
		return status;
	}
	status = i2c_read(cal, sizeof(*cal), true);
	if (status != 0) {
		printf("i2cRead error %d\r\n", status);
		return status;
	}
	status = i2c_stop();
	if (status != 0) {
		printf("i2cStop error %d\r\n", status);
		return status;
	}

	return 0;
}


void i2c_test_main()
{
	initUartDebug();
	i2c_init();
	while(1)
	{
		BMP085Calibration cal;
		if (bmp085LoadCalibration(&cal) == 0) {

			printf("success!\r\n");
			printf("%d %d %d %d %d %d\r\n", cal.ac1, cal.ac2, cal.ac3, cal.ac4, cal.ac5, cal.ac6);
			printf("%d %d\r\n", cal.b1, cal.b2);
			printf("%d %d %d\r\n", cal.mb, cal.mc, cal.md);
		}
	}
}


void adc_test()
{
	adc_init();
	initUartDebug();


	while(1)
	{
		uint16_t value = adc_read(ADC_CHANNEL_PRESSURE);
		GR_DEBUG("adc_value = %d(0x%X)\n", value, value);
	}
}

int main()
{
	//spi_test_main();
	//i2c_test_main();
	adc_test();
	return 0;
}
