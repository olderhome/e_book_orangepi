/*****************************************************************************
* | File      	:   DEV_Config.h
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
* 1.add:
*   UBYTE\UWORD\UDOUBLE
* 2.Change:
*   EPD_RST -> EPD_RST_PIN
*   EPD_DC -> EPD_DC_PIN
*   EPD_CS -> EPD_CS_PIN
*   EPD_BUSY -> EPD_BUSY_PIN
* 3.Remote:
*   EPD_RST_1\EPD_RST_0
*   EPD_DC_1\EPD_DC_0
*   EPD_CS_1\EPD_CS_0
*   EPD_BUSY_1\EPD_BUSY_0
* 3.add:
*   #define DEV_Digital_Write(_pin, _value) bcm2835_gpio_write(_pin, _value)
*   #define DEV_Digital_Read(_pin) bcm2835_gpio_lev(_pin)
*   #define DEV_SPI_WriteByte(__value) bcm2835_spi_transfer(__value)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#if  0 


#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>
#include <stdio.h>

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * e-Paper GPIO
**/
#define EPD_RST_PIN     RST_GPIO_Port, RST_Pin
#define EPD_DC_PIN      DC_GPIO_Port, DC_Pin
#define EPD_PWR_PIN     PWR_GPIO_Port, PWR_Pin
#define EPD_CS_PIN      SPI_CS_GPIO_Port, SPI_CS_Pin
#define EPD_BUSY_PIN    BUSY_GPIO_Port, BUSY_Pin
#define EPD_MOSI_PIN    DIN_GPIO_Port, DIN_Pin
#define EPD_SCLK_PIN    SCK_GPIO_Port, SCK_Pin

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) HAL_GPIO_WritePin(_pin, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define DEV_Digital_Read(_pin) HAL_GPIO_ReadPin(_pin)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) HAL_Delay(__xms);

void DEV_SPI_WriteByte(UBYTE value);
void DEV_SPI_Write_nByte(UBYTE *value, UDOUBLE len);

int DEV_Module_Init(void);
void DEV_Module_Exit(void);
void DEV_GPIO_Init(void);
void DEV_SPI_Init(void);
void DEV_SPI_SendData(UBYTE Reg);
UBYTE DEV_SPI_ReadData(void);

#endif

/*
*
*This is the pin define of orangepione
 +------+-----+----------+------+---+OrangePiH3+---+------+----------+-----+------+
 | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
 +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
 |      |     |     3.3V |      |   |  1 || 2  |   |      | 5V       |     |      |
 |   12 |   0 |    SDA.0 | ALT2 | 0 |  3 || 4  |   |      | 5V       |     |      |
 |   11 |   1 |    SCL.0 | ALT2 | 0 |  5 || 6  |   |      | GND      |     |      |
 |    6 |   2 |      PA6 |  OFF | 0 |  7 || 8  | 0 | ALT3 | TXD.3    | 3   | 13   |
 |      |     |      GND |      |   |  9 || 10 | 0 | ALT3 | RXD.3    | 4   | 14   |
 |    1 |   5 |    RXD.2 | ALT2 | 0 | 11 || 12 | 0 | OFF  | PD14     | 6   | 110  |
 |    0 |   7 |    TXD.2 | ALT2 | 0 | 13 || 14 |   |      | GND      |     |      |
 |    3 |   8 |    CTS.2 |  OFF | 0 | 15 || 16 | 0 | OFF  | PC04     | 9   | 68   |
 |      |     |     3.3V |      |   | 17 || 18 | 0 | OFF  | PC07     | 10  | 71   |
 |   64 |  11 |   MOSI.0 | ALT3 | 0 | 19 || 20 |   |      | GND      |     |      |
 |   65 |  12 |   MISO.0 | ALT3 | 0 | 21 || 22 | 0 | OFF  | RTS.2    | 13  | 2    |
 |   66 |  14 |   SCLK.0 | ALT3 | 0 | 23 || 24 | 0 | ALT3 | CE.0     | 15  | 67   |
 |      |     |      GND |      |   | 25 || 26 | 1 | OUT  | PA21     | 16  | 21   |
 |   19 |  17 |    SDA.1 | ALT3 | 0 | 27 || 28 | 0 | ALT3 | SCL.1    | 18  | 18   |
 |    7 |  19 |     PA07 |  OFF | 0 | 29 || 30 |   |      | GND      |     |      |
 |    8 |  20 |     PA08 |  OFF | 0 | 31 || 32 | 0 | OFF  | RTS.1    | 21  | 200  |
 |    9 |  22 |     PA09 |  OFF | 0 | 33 || 34 |   |      | GND      |     |      |
 |   10 |  23 |     PA10 |  OFF | 0 | 35 || 36 | 0 | OFF  | CTS.1    | 24  | 201  |
 |   20 |  25 |     PA20 |  OFF | 0 | 37 || 38 | 0 | ALT2 | TXD.1    | 26  | 198  |
 |      |     |      GND |      |   | 39 || 40 | 0 | ALT2 | RXD.1    | 27  | 199  |
 +------+-----+----------+------+---+----++----+---+------+----------+-----+------+
 | GPIO | wPi |   Name   | Mode | V | Physical | V | Mode | Name     | wPi | GPIO |
 +------+-----+----------+------+---+OrangePiH3+---+------+----------+-----+------+

Pin connection:

	VCC    ->    3.3
	GND    ->    GND
	DIN    ->    11.MOSI.0(MOSI)
	CLK    ->    14.SCLK.0(SCLK)
	CS     ->    19.PA07
	DC     ->    20.PA08
	RST    ->    22.PA09
	BUSY   ->    23.PA10

In this project,only DIN and CLK has be uses hardware SPI.
*/

#if 1


#include "main.h"
#include <stdint.h>
#include <stdio.h>


//type define 
#define UBYTE   unsigned char 
#define UWORD   unsigned int 
#define UDOUBLE unsigned long long int


#define u8  unsigned char 
#define u32 unsigned int 
#define u64 unsigned long long int

#define s8  signed char 
#define s32 signed int 
#define s64 signed long long int

#define f32 float
#define f64 double
 
#define EPD_MOSI_PIN	11 //MOSI
#define EPD_SCLK_PIN	14 //SCLK
#define EPD_RST_PIN     19
#define EPD_DC_PIN      20
#define EPD_PWR_PIN     25 //pwr
#define EPD_CS_PIN      22
#define EPD_BUSY_PIN    23



void DEV_Digital_Write(int pin, int value);

//pin read
int DEV_Digital_Read(int pin);
//delay
void DEV_Delay_ms(u32 delay_time);
//SPI read/write
int DEV_SPI_WriteByte(UBYTE value);
void DEV_SPI_Write_nByte(UBYTE *value, UDOUBLE len);
void DEV_GPIO_Init();
void DEV_SPI_Init();
//e_paper组件初始化
int DEV_Module_Init(void);
//e_paper组件断开
void DEV_Module_Exit(void);




#endif


#endif
