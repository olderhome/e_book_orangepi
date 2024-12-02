#ifndef __EPAPER_TXT
#define __EPAPER_TXT




#include "epaper_scream.h"
#include "EPD_2in9_V2.h"

#if 1 	//CN config

#define SIZE_STEP 8										//存储字模的存储空间大小

//中文设置
#define CN_FONT_SIZE 16  // 根据需要设置字体大小中文是方块字，文字大小为CN_FONT_SIZE*CN_FONT_SIZE
#define CN_FONT_HEIGHT	CN_FONT_SIZE
#define CN_FONT_WIDTH	(CN_FONT_SIZE == 12 ? 16 : CN_FONT_SIZE)  	//对于12号字体宽度特殊处理
#define GB2312_CODE_SIZE 2

//一汉字占用的存储空间大小
#define FOAT_BUF_LEN     CN_FONT_HEIGHT*CN_FONT_WIDTH/SIZE_STEP		//32


//汉字的像素宽度
#define HZ_PIXEL_WIDTH      16
//汉字的字节宽度
#define HZ_BYTE_WIDTH       2

//ascii码的像素宽度
#define ASC_PIXEL_WIDTH     11
//ascii码的字节宽度
#define ASC_BYTE_WIDTH      1
//每行最大的英文长度
#define ASC_MAX_LENTH       (EPD_2IN9_V2_HEIGHT - LEFT_SCREAM_SPACE)/ASC_PIXEL_WIDTH //296/11

#endif 





void TXT_read_font_CN(const char *char_code,char *font_CN, int font_size);



void diag_data(unsigned char *data, unsigned int size);
void print_font_data(char *font_CN);
void TXT_readfile_init(char * filename ,s_scream_show* scream_show);


#endif