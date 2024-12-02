#ifndef __EPAPER_SCREAM_H_
#define __EPAPER_SCREAM_H_


#include "DEV_Config.h"




//��������

#define LINES_NUM 6			//ÿҳ�����:6��

#define TITLE_ENABLE		//��˵���У�˵����Ϣ

#ifdef TITLE_ENABLE

#define TITLE_LINE_NUM 0	//��0����˵����
#define TEXT_LINES_NUM	5	//�ı�������ʾ����:5��

#else
#define TEXT_LINES_NUM	6	//�ı�������ʾ����:6��
#endif


#define LEFT_SCREAM_SPACE	10	//�������Ԥ���ռ�
#define TOP_SCREAM_SPACE	10	//�����Ϸ�Ԥ���ռ�
#define RIGHT_SCREAM_SPACE	0	//�����ұ�Ԥ���ռ�
#define BOTTOM_SCREAM_SPACE	0	//�����·�Ԥ���ռ�


#define LINES_BUF_SIZE	40 	//ÿ�л�������ȣ�40�ֽڣ�ÿ�����洢17�����֣���34�ֽ�


#define MARK_FILE		"mark"




typedef struct s_page s_page;
typedef struct s_screen_show s_screen_show;
typedef struct s_mark s_mark;



//ҳ����Ϣ�ṹ��
 struct s_page
{
	 s_page *prev;
	 s_page *next;

	int current_page_id; //ҳ���ţ����ǵڼ�ҳ����
	int page_sleek;		//�ļ���ʼλ��
	int page_lenth;		//ÿҳ����
	int lines_lenth[LINES_NUM];	//ÿ�г���
	
};

//ҳ����ʾ�ṹ��
 struct s_screen_show
{

	UBYTE *BlackImage;		//��Ļͼ������
	char readfilename[256];		//txt�ļ�����
	UWORD Imagesize;		//��Ļͼ�������С = 128*296/8 = 4736

	//��������ʾ�Ŀ�Ⱥ͸߶�
	//��ʾ�������У���Ⱥ͸߶�Ū���ˣ�����ֻ�ܽ���ʹ���
	//����������������ַ������Ļ���������ص�һ��ƽ��
	//max_hight���������ַ���ͬ�򣬺���һֱ����ô�趨
	UWORD max_width;		//��Ļ��� 128����
	UWORD max_hight;		//��Ļ�߶� 296����

	char txt_line_buf[LINES_NUM][64];		//��ʾ�ı���ҳ����
	
	s_page *page_linklist;
	unsigned int page_num;

};

struct s_mark
{
	int mark_id;			//��ǩid�ţ�Ψһ��ʶ������
	char file_name[256]; 	//txt�ļ�����
	int page_id;			//��ǩҳ�� 
};


//typedef struct s_page s_page;
//typedef struct s_screen_show s_screen_show;

//����ǩ���в����ĺ���
int Config_mark_read(s_mark *mark, char *filename);
int Config_mark_write(s_mark *mark);
void Config_mark_clean(char *filename);



void Screen_DEV_Init();
void Screen_init();
void Screen_print_page(const s_screen_show *screen,char *acode);
void Screen_show_page_test();
void chinese_show_test();
void Test_print_page(s_page *p_page,char * filename);




#endif



