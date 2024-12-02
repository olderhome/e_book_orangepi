#ifndef __EPAPER_SCREAM_H_
#define __EPAPER_SCREAM_H_


#include "DEV_Config.h"




//界面设置

#define LINES_NUM 6			//每页最长长度:6行

#define TITLE_ENABLE		//有说明行，说明信息

#ifdef TITLE_ENABLE

#define TITLE_LINE_NUM 0	//第0行是说明行
#define TEXT_LINES_NUM	5	//文本内容显示行数:5行

#else
#define TEXT_LINES_NUM	6	//文本内容显示行数:6行
#endif


#define LEFT_SCREAM_SPACE	10	//文字左边预留空间
#define TOP_SCREAM_SPACE	10	//文字上方预留空间
#define RIGHT_SCREAM_SPACE	0	//文字右边预留空间
#define BOTTOM_SCREAM_SPACE	0	//文字下方预留空间


#define LINES_BUF_SIZE	40 	//每行缓存最长长度：40字节，每行最多存储17个汉字，共34字节


#define MARK_FILE		"mark"




typedef struct s_page s_page;
typedef struct s_screen_show s_screen_show;
typedef struct s_mark s_mark;



//页面信息结构体
 struct s_page
{
	 s_page *prev;
	 s_page *next;

	int current_page_id; //页面编号，这是第几页文字
	int page_sleek;		//文件起始位置
	int page_lenth;		//每页长度
	int lines_lenth[LINES_NUM];	//每行长度
	
};

//页面显示结构体
 struct s_screen_show
{

	UBYTE *BlackImage;		//屏幕图像数组
	char readfilename[256];		//txt文件名称
	UWORD Imagesize;		//屏幕图像数组大小 = 128*296/8 = 4736

	//下面是显示的宽度和高度
	//在示例程序当中，宽度和高度弄反了，这里只能将错就错了
	//在这里，我们设置文字方向和屏幕更长的像素的一方平行
	//max_hight方向与文字方向同向，后面一直会这么设定
	UWORD max_width;		//屏幕宽度 128像素
	UWORD max_hight;		//屏幕高度 296像素

	char txt_line_buf[LINES_NUM][64];		//显示文本的页缓存
	
	s_page *page_linklist;
	unsigned int page_num;

};

struct s_mark
{
	int mark_id;			//书签id号，唯一标识，递增
	char file_name[256]; 	//txt文件名称
	int page_id;			//书签页面 
};


//typedef struct s_page s_page;
//typedef struct s_screen_show s_screen_show;

//对书签进行操作的函数
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



