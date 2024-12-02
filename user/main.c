#include <stdio.h>
#include "EPD_Test.h"
#include <unistd.h>
#include "DEV_Config.h"
#include <wiringPi.h>
#include "epaper_scream.h"
#include "EPD_2in9_V2.h"
#include "epaper_txt.h"

extern s_screen_show g_screen;

void cleanup(void)
{
	printf("clean s_screen_show\n");
	TXT_closefile(&g_screen);
}


int main()
{
	char acode[32];
	printf("Testing e_paper\r\n");

	//硬件初始化
	wiringPiSetup();

	//回收函数初始化，当程序exit或者return时，cleanup执行
	atexit(cleanup);

	//test_chinese_byte();

#if 1
	//屏幕显示初始化
	Screen_DEV_Init();
	Screen_init();
	Screen_show_page_test();

	//sleep(2);
#endif
	TXT_readfile_init("testfile.txt" ,&g_screen);

	while(1)
	{
		//chinese_show_test();
		//Scream_show_page_test();
	    //EPD_2IN9_V2_Display_Base(g_scream.BlackImage);
		printf("input instruct:");
		scanf("%s",&acode);
		getchar();
		Screen_print_page(&g_screen,acode);
		//TXT_closefile(&g_scream);
		//sleep(1);
	}
	return 0;
}

