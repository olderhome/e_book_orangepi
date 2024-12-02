#include <stdio.h>
#include "EPD_Test.h"
#include <unistd.h>
#include "DEV_Config.h"
#include <wiringPi.h>
#include "epaper_scream.h"
#include "EPD_2in9_V2.h"
#include "epaper_txt.h"

extern s_scream_show g_scream;

int main()
{
	printf("Testing e_paper\r\n");

	wiringPiSetup();

	//test_chinese_byte();

#if 1
	//∆¡ƒªœ‘ æ≥ı ºªØ
	Scream_DEV_Init();
	Scream_init();
	Scream_show_page_test();

	sleep(2);
#endif

	while(1)
	{
		//chinese_show_test();
		//Scream_show_page_test();
	    //EPD_2IN9_V2_Display_Base(g_scream.BlackImage);
		TXT_readfile_init("testfile.txt" ,&g_scream);
		//TXT_closefile(&g_scream);
		sleep(1);
	}
	return 0;
}

