#ifndef __EPAPER_TXT
#define __EPAPER_TXT




#include "epaper_scream.h"
#include "EPD_2in9_V2.h"

#if 1 	//CN config

#define SIZE_STEP 8										//�洢��ģ�Ĵ洢�ռ��С

//��������
#define CN_FONT_SIZE 16  // ������Ҫ���������С�����Ƿ����֣����ִ�СΪCN_FONT_SIZE*CN_FONT_SIZE
#define CN_FONT_HEIGHT	CN_FONT_SIZE
#define CN_FONT_WIDTH	(CN_FONT_SIZE == 12 ? 16 : CN_FONT_SIZE)  	//����12�����������⴦��
#define GB2312_CODE_SIZE 2

//һ����ռ�õĴ洢�ռ��С
#define FOAT_BUF_LEN     CN_FONT_HEIGHT*CN_FONT_WIDTH/SIZE_STEP		//32


//���ֵ����ؿ��
#define HZ_PIXEL_WIDTH      16
//���ֵ��ֽڿ��
#define HZ_BYTE_WIDTH       2

//ascii������ؿ��
#define ASC_PIXEL_WIDTH     11
//ascii����ֽڿ��
#define ASC_BYTE_WIDTH      1
//ÿ������Ӣ�ĳ���
#define ASC_MAX_LENTH       (EPD_2IN9_V2_HEIGHT - LEFT_SCREAM_SPACE)/ASC_PIXEL_WIDTH //296/11

#endif 





void TXT_read_font_CN(const char *char_code,char *font_CN, int font_size);



void diag_data(unsigned char *data, unsigned int size);
void print_font_data(char *font_CN);
void TXT_readfile_init(char * filename ,s_scream_show* scream_show);


#endif