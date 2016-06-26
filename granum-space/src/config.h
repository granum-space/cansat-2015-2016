/*
 * config.h
 *
 *  Created on: 27 мая 2016 г.
 *      Author: developer
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/io.h>

// DHT22
#define DHT_PORT PORTC	// Регистр PORT порта, на котором подсоединен датчик DHT022
#define DHT_PPIN PINC	// Регистр PIN порта на котором подсоединен датчик DHT022
#define DHT_DDR DDRC	// Регистр ВВК порта на котором подсоединен датчик DHT022
#define DHT_PIN 4		// Номер пина в порту

// i2c
#define I2C_TIMEOUT_COUNT 10000
#define I2C_TIMEOUT_US 10
#define F_SCL 400000

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
#define RF_TARGET_ADDR 0x7e, 0x7e, 0x7e, 0x7e // адрес получателя

#define CTSDDR DDRC
#define CTSPIN PINC
#define CTSLEG 2

#define PDDDR DDRC
#define PDPORT PORTC
#define PDLEG 3

#define RTSDDR DDRC
#define RTSPORT PORTC
#define RTSLEG 5

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

//acc
#define DATARATE (1<<3)|(1<<2)|1
#define FIFOSET (1<<7)|32
#define POWERCTL (1<<3)

#define ACC_ADRESS 0x53

#define DEVID 0x00
#define THRESH_SHOCK 0x1D
#define OFSX 0x1E
#define OFSY 0x1F
#define OFSZ 0x20
#define DUR 0x21
#define LATENT 0x22
#define WINDOW 0x23
#define TRESH_ACT 0x24
#define TRESH_INACT 0x25
#define TIME_INACT 0x26
#define ACT_INACT_CTL 0x27
#define SHOCK_AXES 0x2A
#define ACT_SHOCK_STATUS 0x2B
#define BW_RATE 0x2C
#define POWER_CTL 0x2D
#define INT_ENABLE 0x2E
#define INT_MAP 0x2F
#define INT_SOURCE 0x30
#define DATA_FORMAT 0x31
#define DATAX0 0x32
#define DATAX1 0x33
#define DATAY0 0x34
#define DATAY1 0x35
#define DATAZ0 0x36
#define DATAZ1 0x37
#define FIFO_CTL 0x38
#define FIFO_STATUS 0x39

//soilres
#define SRDDR DDRA
#define SRPORT PORTA
#define SR1MODE 0
#define SR1ON 1
#define SR2MODE 2
#define SR2ON 3
#define SR3MODE 4
#define SR3ON 5

#endif /* CONFIG_H_ */
