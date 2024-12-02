/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
*----------------
* |	This version:   V2.0
* | Date        :   2018-10-30
* | Info        :
# ******************************************************************************
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
#include "DEV_Config.h"
#include <wiringPi.h>
#include <unistd.h>
#include "bsp_spi.h"
#include "wiringPiSPI.h"

#include "Debug.h"

extern s_spi g_spi0;

#if 1

//pin write
void DEV_Digital_Write(int pin, int value)
{
	digitalWrite(pin , value);
}

//pin read
int DEV_Digital_Read(int pin)
{
	int result = 0;
	result = digitalRead(pin);
	return result;
}

void DEV_Delay_ms(u32 delay_time)
{
	usleep(delay_time * 1000);
}


int DEV_SPI_WriteByte(UBYTE value)
{
	int result;
	result = wiringPiSPIDataRW(0,&value,1);
	return result;
}


void DEV_SPI_Write_nByte(UBYTE *value, UDOUBLE len)
{
	wiringPiSPIDataRW(0,value,len);
}

void DEV_GPIO_Init()
{
	//pin mode set
	pinMode (EPD_RST_PIN, OUTPUT);
	pinMode (EPD_DC_PIN, OUTPUT);
	pinMode (EPD_PWR_PIN, OUTPUT);
	pinMode (EPD_CS_PIN, OUTPUT);
	pinMode (EPD_BUSY_PIN, OUTPUT);
	
	//pin status init
	digitalWrite (EPD_RST_PIN, LOW);
	digitalWrite (EPD_DC_PIN, LOW);
	digitalWrite (EPD_PWR_PIN, LOW);
	digitalWrite (EPD_CS_PIN, LOW);
	digitalWrite (EPD_BUSY_PIN, LOW);

}

void DEV_SPI_Init()
{
	u8 result = 0 ;
	SPI_struct_init();
	result = wiringPiSPISetupMode(0,0,10000000,0);

	if(result == -1)
	{
		Debug("SPI init error\r\n");
	}
	else
	{
		Debug("SPI init success\r\n");
	}
}

//e_paper组件初始化
int DEV_Module_Init(void)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    //open 5V
	DEV_Digital_Write(EPD_PWR_PIN, 1);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    return 0;
	
}
//e_paper组件断开
void DEV_Module_Exit(void)
{

    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    //close 5V
	DEV_Digital_Write(EPD_PWR_PIN, 0);
    DEV_Digital_Write(EPD_RST_PIN, 0);
}



#endif





