/**
  ******************************************************************************
  * @file    fonts.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   Header for fonts.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONTS_H
#define __FONTS_H

/*最大字体微软雅黑24 (32x41) */
#define MAX_HEIGHT_FONT         41
#define MAX_WIDTH_FONT          32
#define OFFSET_BITMAP           

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


/* Defines ------------------------------------------------------------------*/
#define SIZE_STEP 8										//存储字模的存储空间大小

//中文设置
#define CN_FONT_SIZE 16  // 根据需要设置字体大小中文是方块字，文字大小为CN_FONT_SIZE*CN_FONT_SIZE
#define CN_FONT_HEIGHT	CN_FONT_SIZE
#define CN_FONT_WIDTH	(CN_FONT_SIZE == 12 ? 16 : CN_FONT_SIZE)  	//对于12号字体宽度特殊处理
#define GB2312_CODE_SIZE 2

//一汉字占用的存储空间大小
#define FOAT_BUF_LEN     CN_FONT_HEIGHT*CN_FONT_WIDTH/SIZE_STEP		//32


//ASCII
typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t ASCII_Width;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;


//GB2312
typedef struct                                          // 汉字字模数据结构
{
  unsigned char index[2];                               // 汉字内码索引
  char matrix[MAX_HEIGHT_FONT*MAX_WIDTH_FONT/8];  // 点阵码数据
}CH_CN;


typedef struct
{    
  CH_CN *table;
  uint16_t size;
  uint16_t ASCII_Width;
  uint16_t Width;
  uint16_t Height;
  
}cFONT;

extern sFONT Font24;
extern sFONT Font20;
extern sFONT Font16;
extern sFONT Font12;
extern sFONT Font8;

extern cFONT Font12CN;
extern cFONT Font16CN;
extern cFONT Font24CN;



//CN config ------------------------------------------------------------------

//汉字的字模库名称
#define HZK_PART		"HZK16"
//汉字的像素宽度
#define HZ_PIXEL_WIDTH      16
//汉字的字节宽度
#define HZ_BYTE_WIDTH       2

//EN config ------------------------------------------------------------------

//ascii码的像素宽度
#define ASC_PIXEL_WIDTH     11
//ascii码的字节宽度
#define ASC_BYTE_WIDTH      1
//每行最大的英文长度
#define ASC_MAX_LENTH       (EPD_2IN9_V2_HEIGHT - LEFT_SCREAM_SPACE)/ASC_PIXEL_WIDTH //296/11


#ifdef __cplusplus
}
#endif






#endif /* __FONTS_H */
 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
