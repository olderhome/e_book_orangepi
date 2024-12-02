/*****************************************************************************
* | File      	:  	epaper_scream.c
* | Author      :   Trauma
* | Function    :   负责界面与显示
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   
* | Info        :
* -----------------------------------------------------------------------------
******************************************************************************/
#include "epaper_scream.h"

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "ImageData.h"
#include "Debug.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "EPD_Test.h"
#include "EPD_2in9_V2.h"
#include "epaper_txt.h"
#include "epaper_scream.h"

char read_buf[512];

s_screen_show g_screen;



void Screen_DEV_Init()
{

	//GPIO初始化
	DEV_GPIO_Init();
	//SPI初始化
	DEV_SPI_Init();
	//e_paper组件初始化
	DEV_Module_Init();

}


void Screen_init()
{

	//e_paper系统初始化
	EPD_2IN9_V2_Init();
	//e_paper清屏
	EPD_2IN9_V2_Clear();
	DEV_Delay_ms(1000);
	
	//Create a new image cache 
	g_screen.Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
	g_screen.max_width = EPD_2IN9_V2_WIDTH;
	g_screen.max_hight = EPD_2IN9_V2_HEIGHT;

	if((g_screen.BlackImage = (UBYTE *)malloc(g_screen.Imagesize)) == NULL) {
		Debug("Failed to apply for black memory...\r\n");
		//return -1;
	}
	memset(g_screen.BlackImage , 0 , g_screen.Imagesize);
	EPD_2IN9_V2_Init_Fast();
	Paint_NewImage(g_screen.BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);	
	

}



void Screen_show_page_test()
{

	// 1.Select Image
	Paint_SelectImage(g_screen.BlackImage);

	// 2.Clean Image
	memset(g_screen.BlackImage , 0 ,g_screen.Imagesize);

	// 3.Drawing on the image
	Paint_DrawString(10, 10, "诗曰：", &Font16CN , &Font16, WHITE, BLACK);
	Paint_DrawString(10, 30, "混沌未分天地乱，茫茫渺渺无人见。", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 50, "自从盘古破鸿蒙，开辟从兹清浊辨。", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 70, "覆载群生仰至仁，发明万物皆成善。", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 90, "欲知造化会元功，须看西游释厄传。", &Font16CN, &Font16, WHITE, BLACK);
	//Paint_DrawString(10, 110, "hello world", &Font12,BLACK , WHITE);
	Paint_DrawString(10, 110,"你好Trauma你好", &Font16CN,&Font16, WHITE, BLACK);

	// 4.Display image
	EPD_2IN9_V2_Display_Base(g_screen.BlackImage);
}



void chinese_show_test()
{
	Debug("EPD_2IN9_V2_test Demo\r\n");
	if(DEV_Module_Init()!=0){
		//return -1;
	}

	Debug("e-Paper Init and Clear...\r\n");
	EPD_2IN9_V2_Init();
	EPD_2IN9_V2_Clear();
	DEV_Delay_ms(1000);

	//Create a new image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		Debug("Failed to apply for black memory...\r\n");
		//return -1;
	}
	//printf("Paint_NewImage\r\n");
	//Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
	//Paint_Clear(WHITE);
	//DEV_Delay_ms(1000);

#if 0  //show image for array  
	Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);  
	printf("show image for array\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMap(gImage_2in9);

	EPD_2IN9_V2_Display(BlackImage);
	DEV_Delay_ms(3000);
#endif

#if 1  // Drawing on the image
#if 1
	EPD_2IN9_V2_Init_Fast();
	Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);	
	Debug("Drawing\r\n");
	//1.Select Image
	Paint_SelectImage(BlackImage);
	//Paint_Clear(WHITE);
	//Paint_Clear(BLACK);
#endif
	
	// 2.Drawing on the image
	#if 0
	Debug("Drawing:BlackImage\r\n");
	Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

	Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

	Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

	Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

	Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
	Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);

	Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
	Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);

	//Paint_DrawString_CN(130, 0, "H", &Font16CN, WHITE, BLACK);
	#endif
	Paint_DrawString(10, 10, "诗曰：", &Font16CN , &Font16, WHITE, BLACK);
	Paint_DrawString(10, 30, "混沌未分天地乱，茫茫渺渺无人见。", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 50, "自从盘古破鸿蒙，开辟从兹清浊辨。", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 70, "覆载群生仰至仁，发明万物皆成善。", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 90, "欲知造化会元功，须看西游释厄传。", &Font16CN, &Font16, WHITE, BLACK);
	//Paint_DrawString(10, 110, "hello world", &Font12,BLACK , WHITE);
	Paint_DrawString(10, 110,"你好Trauma你好", &Font16CN,&Font16, WHITE, BLACK);
	//Paint_DrawString(10, 110, "123456789ABCDEFGHIJKLMN你好", &Font16CN, &Font16, WHITE, BLACK);

	#if 0
	cFONT* font = &Font16CN;
	UWORD Color_Foreground = WHITE;
	UWORD Color_Background = BLACK;
	char* ptr = font->table[0].matrix;
	x = 130;
	y = 20;

	//TXT_read_font_CN("我",ptr, 16);


	for (j = 0; j < font->Height; j++) {
		for (i = 0; i < font->Width; i++) {
			if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
				if (*ptr & (0x80 >> (i % 8))) {
					//Debug("set point x=%d y=%d\r\n",x + i,y + j);
					Paint_SetPixel(x + i, y + j, Color_Foreground);
					// Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
				}
			} else {
				if (*ptr & (0x80 >> (i % 8))) {
					//Debug("set point x=%d y=%d\r\n",x + i,y + j);
					Paint_SetPixel(x + i, y + j, Color_Foreground);
					// Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
				} else {
					//Debug("set point x=%d y=%d\r\n",x + i,y + j);
					Paint_SetPixel(x + i, y + j, Color_Background);
					// Paint_DrawPoint(x + i, y + j, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
				}
			}
			if (i % 8 == 7) {
				ptr++;
			}
		}
		if (font->Width % 8 != 0) {
			ptr++;
		}
	}


	#endif

	
	#if 0
	for(i = 130; i< 180; i++)
	{
		for(j = 0 ;j<20;j++)
		{
			Paint_SetPixel(i,j,GRAY1);
		}
	}
	for(i = 130; i< 150; i++)
	{
		for(j = 20 ;j<40;j++)
		{
			Paint_SetPixel(i,j,GRAY4);
		}
	}
	#endif
	//memset(BlackImage,0x85,Imagesize);

	EPD_2IN9_V2_Display_Base(BlackImage);
	//DEV_Delay_ms(3000);
	#endif


}


/**
 * @brief 打印屏幕页面内容
 * 
 * 该函数用于根据提供的屏幕对象和页面代码，打印当前页面的内容。
 * 它支持翻页功能，可以通过传入的acode参数来控制翻到下一页（'n'）或上一页（'p'）。
 * 
 * @param screen 指向屏幕显示对象的指针
 * @param acode 控制翻页和读取页面行动的字符。
 				'n'表示下一页，'p'表示上一页，'r'表示转到书签，'w'表示设置书签。
 */
void Screen_print_page(const s_screen_show *screen,char *acode)
{
	s_page *p_frist_page = screen->page_linklist;
	s_page *p_page = screen->page_linklist;
	unsigned int i = 0;
	char fread_buf[40] = {0};
	unsigned int page_seek = 0;
	FILE *fp;
	


	

	if(acode[0] == 'n')
	{
		if(p_page->next != NULL)
		{
			p_page = p_page->next;
		}
		else
		{
			printf("It is last page\n");
		}
	}
	if(acode[0] == 'p')
	{
		if(p_page->next != NULL)
		{
			p_page = p_page->prev;
		}
		else
		{
			printf("It is first page\n");
		}
	}
	if(acode[0] == 'r')
	{
		if(p_page->next != NULL)
		{
			p_page = p_page->prev;
		}
		else
		{
			printf("It is first page\n");
		}
	}
	if(acode[0] == 'w')
	{
		if(p_page->next != NULL)
		{
			p_page = p_page->prev;
		}
		else
		{
			printf("It is first page\n");
		}
	}

	page_seek = p_page->page_sleek;

	sprintf(fread_buf,"page %d//%d",p_page->current_page_id,screen->page_num);
	Paint_DrawString(10, 10, fread_buf, &Font16CN , &Font16, WHITE, BLACK);
	printf("%s\r\n",fread_buf);
	
	
	for(i = 0 ; i < TEXT_LINES_NUM ; i++)
	{
		memset(fread_buf, 0 , sizeof(fread_buf));
		fseek(fp, page_seek, SEEK_SET);
	    fread(fread_buf, 1, p_page->lines_lenth[i], fp);
		page_seek = page_seek + p_page->lines_lenth[i];

		Paint_DrawString(LEFT_SCREAM_SPACE, LEFT_SCREAM_SPACE + (1+i)*20, fread_buf, &Font16CN , &Font16, WHITE, BLACK);
	}
	EPD_2IN9_V2_Display_Base(screen->BlackImage);
	//关闭文件
	fclose(fp);
	sleep(2);
}


//输出一个界面
void Test_print_page(s_page *p_page,char * filename)
{
	unsigned int i;
	unsigned int page_seek = 0;
	char fread_buf[40] = {0};
	FILE *fp;
	page_seek = p_page->page_sleek;


	fp = fopen(filename, "rb");
	memset(g_screen.BlackImage , 0 ,g_screen.Imagesize);

	sprintf(fread_buf,"page %d",p_page->current_page_id);
	Paint_DrawString(10, 10, fread_buf, &Font16CN , &Font16, WHITE, BLACK);
	printf("%s\r\n",fread_buf);
	
	
	for(i = 0 ; i < TEXT_LINES_NUM ; i++)
	{
		memset(fread_buf, 0 , sizeof(fread_buf));
		fseek(fp, page_seek, SEEK_SET);
	    fread(fread_buf, 1, p_page->lines_lenth[i], fp);
		page_seek = page_seek + p_page->lines_lenth[i];

		Paint_DrawString(LEFT_SCREAM_SPACE, LEFT_SCREAM_SPACE + (1+i)*20, fread_buf, &Font16CN , &Font16, WHITE, BLACK);
		//EPD_2IN9_V2_Display_Base(g_screen.BlackImage);
		//sleep(2);
		//printf("\t\t%s\r\n",fread_buf);
	}

	EPD_2IN9_V2_Display_Base(g_screen.BlackImage);
	//关闭文件
	fclose(fp);
	sleep(2);
}

//初始化s_scream_show
void s_scream_show_init(s_screen_show *screen)
{
	memset(screen , 0 ,sizeof(screen));
}


//选择文件
void Screen_select_file()
{

}


