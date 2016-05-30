/*
 * config.h
 *
 *  Created on: 27 мая 2016 г.
 *      Author: developer
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>


// datautils
//#define RPORT PORTC
//#define RDDR DDRC
//#define RCFGNUM 1
//#define RRTSNUM 2
//#define RCTSNUM 3

//#define CONFIG RPORT &= ~(1<<RCFGNUM);
//#define OPER RPORT |= (1<<RCFGNUM);
//#define RTS_EN RPORT &= ~(1<<RRTSNUM);
//#define RTS_DIS RPORT |= (1<<RRTSNUM);
//#define CTS (RPIN & (1<<RCTSNUM));

// DHT22
#define DHT_PORT PORTC	// Регистр PORT порта, на котором подсоединен датчик DHT022
#define DHT_PPIN PINC	// Регистр PIN порта на котором подсоединен датчик DHT022
#define DHT_DDR DDRC	// Регистр ВВК порта на котором подсоединен датчик DHT022
#define DHT_PIN 4		// Номер пина в порту

// i2c
#define I2C_TIMEOUT_COUNT 30
#define I2C_TIMEOUT_US 10
#define F_SCL 600000

// onewire
#define ONE_WIRE_PORT PORTC
#define ONE_WIRE_PPIN PINC
#define ONE_WIRE_DDR DDRC
#define ONE_WIRE_PIN 0

// rxq2-433
#define CFGDDR DDRC
#define CFGLEG 1
#define CFGPORT PORTC

#define RXQ2_BAUD_RATE 9600

#define RF_CH 100 // частота канала передачи при добавлении 1 и увеличивается на 100kHz
#define RF_POWER 3 // Мощность радиопередатчика. Значения 0: -10dBm, 1: -2dBm, 2: +6dBm, 3: +10dBm
#define RF_RX_PACKET 30 // размер принимаемых  пакетов (30 максимум)
#define RF_TX_PACKET 30 // размер отсылаемых пакетов (30 максимум)
#define RF_SELF_ADDR  0x01, 0x02, 0x03, 0x04 // адрес модуля
#define RF_TARGET_ADDR 0x5a, 0x5b, 0x5c, 0x5f // адрес получателя

#define CTSDDR DDRC
#define CTSPIN PINC
#define CTSLEG 2

// sdcard
#define SPIDDR DDRB
#define SPIPORT PORTB

#if defined (__AVR_ATmega328P__)
#	define SS 2
#elif defined (__AVR_ATmega128__)
#	define SS 0
#endif

// spi
#define SPI_PORTX PORTB
#define SPI_DDRX DDRB

#if defined (__AVR_ATmega328P__)
#	define SPI_MISO 4
#	define SPI_MOSI 3
#	define SPI_SCK 5
#	define SPI_SS 2
#elif defined (__AVR_ATmega128__)
#	define SPI_MISO 3
#	define SPI_MOSI 2
#	define SPI_SCK 1
#	define SPI_SS 0
#endif

// debug
// скорость работы отладочного UART
#define UART_DEBUG_BAUD_RATE 9600

#endif /* CONFIG_H_ */
