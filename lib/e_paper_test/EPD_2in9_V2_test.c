/*****************************************************************************
* | File      	:   EPD_2IN9_V2_test.c
* | Author      :   Waveshare team
* | Function    :   2.9inch e-paper V2 test demo
* | Info        :
*----------------
* |	This version:   V1.1
* | Date        :   2023-08-30
* | Info        :
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
#include "EPD_Test.h"
#include "EPD_2in9_V2.h"
#include "epaper_txt.h"

#if 0
int EPD_test(void)
{
    printf("EPD_2IN9_V2_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
	EPD_2IN9_V2_Init();
    EPD_2IN9_V2_Clear();
    DEV_Delay_ms(1000);

    //Create a new image cache
    UBYTE *BlackImage;
    UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
	Paint_Clear(WHITE);

#if 1  //show image for array  
    Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);  
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(gImage_2in9);

    EPD_2IN9_V2_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1  // Drawing on the image
    EPD_2IN9_V2_Init_Fast();
	Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);  	
    printf("Drawing\r\n");
    //1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
	
    // 2.Drawing on the image
    printf("Drawing:BlackImage\r\n");
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

    //Paint_DrawString_CN(130, 0, "你好abc", &Font12CN, BLACK, WHITE);
    //Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, WHITE, BLACK);

    EPD_2IN9_V2_Display_Base(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1   //Partial refresh, example shows time    		
	Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);  
    printf("Partial refresh\r\n");
    Paint_SelectImage(BlackImage);
	
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 10;
    for (;;) {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60) {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60) {
                sPaint_time.Hour =  sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24) {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_ClearWindows(150, 80, 150 + Font20.Width * 7, 80 + Font20.Height, WHITE);
        Paint_DrawTime(150, 80, &sPaint_time, &Font20, WHITE, BLACK);

        num = num - 1;
        if(num == 0) {
            break;
        }
		EPD_2IN9_V2_Display_Partial(BlackImage);
        DEV_Delay_ms(500);//Analog clock 1s
    }
#endif

#if 1 // show image for array
    free(BlackImage);
    printf("show Gray------------------------\r\n");
    Imagesize = ((EPD_2IN9_V2_WIDTH % 4 == 0)? (EPD_2IN9_V2_WIDTH / 4 ): (EPD_2IN9_V2_WIDTH / 4 + 1)) * EPD_2IN9_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    EPD_2IN9_V2_Gray4_Init();
    printf("4 grayscale display\r\n");
    Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);  	
    Paint_SetScale(4);
    Paint_Clear(0xff);
    
    Paint_DrawPoint(10, 80, GRAY4, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, GRAY4, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, GRAY4, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, GRAY4, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, GRAY4, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 70, 70, 120, GRAY4, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, GRAY4, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(45, 95, 20, GRAY4, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(105, 95, 20, GRAY2, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, GRAY4, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, GRAY4, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, GRAY4, GRAY1);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, GRAY3, GRAY1);
    Paint_DrawNum(10, 33, 123456789, &Font12, GRAY4, GRAY2);
    Paint_DrawNum(10, 50, 987654321, &Font16, GRAY1, GRAY4);
	
	#if 0
    Paint_DrawString_CN(150, 0,"你好abc", &Font12CN, GRAY4, GRAY1);
    Paint_DrawString_CN(150, 20,"你好abc", &Font12CN, GRAY3, GRAY2);
    Paint_DrawString_CN(150, 40,"你好abc", &Font12CN, GRAY2, GRAY3);
    Paint_DrawString_CN(150, 60,"你好abc", &Font12CN, GRAY1, GRAY4);
    Paint_DrawString_CN(150, 80, "微雪电子", &Font24CN, GRAY1, GRAY4);
	#endif
	#if 1
    Paint_DrawString_CN(150, 0,"你好abc", &Font16CN, GRAY4, GRAY1);
    Paint_DrawString_CN(150, 20,"你好abc", &Font16CN, GRAY3, GRAY2);
    Paint_DrawString_CN(150, 40,"你好abc", &Font16CN, GRAY2, GRAY3);
    Paint_DrawString_CN(150, 60,"你好abc", &Font16CN, GRAY1, GRAY4);
    Paint_DrawString_CN(150, 80, "微雪电子", &Font16CN, GRAY1, GRAY4);
	#endif
    EPD_2IN9_V2_4GrayDisplay(BlackImage);
    DEV_Delay_ms(30000);


    Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 0, WHITE);
    Paint_SetScale(4);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(gImage_2in9_4Gray);
    EPD_2IN9_V2_4GrayDisplay(BlackImage);
    DEV_Delay_ms(30000);

#endif
    
	printf("Clear...\r\n");
	EPD_2IN9_V2_Init();
    EPD_2IN9_V2_Clear();
	
    printf("Goto Sleep...\r\n");
    EPD_2IN9_V2_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    return 0;
}

#endif
#if 0
void chinese_show_test()
{
	int i,j ,x,y;

		printf("EPD_2IN9_V2_test Demo\r\n");
		if(DEV_Module_Init()!=0){
			//return -1;
		}
	
		printf("e-Paper Init and Clear...\r\n");
		EPD_2IN9_V2_Init();
		EPD_2IN9_V2_Clear();
		DEV_Delay_ms(1000);
	
		//Create a new image cache
		UBYTE *BlackImage;
		UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
		if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			//return -1;
		}
		printf("Paint_NewImage\r\n");
		Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
		Paint_Clear(WHITE);
		DEV_Delay_ms(1000);
	
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
		EPD_2IN9_V2_Init_Fast();
		Paint_NewImage(BlackImage, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);	
		printf("Drawing\r\n");
		//1.Select Image
		Paint_SelectImage(BlackImage);
		//Paint_Clear(WHITE);
		Paint_Clear(BLACK);
		
		// 2.Drawing on the image
		#if 0
		printf("Drawing:BlackImage\r\n");
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

		TXT_read_font_CN("我",ptr, 16);


		for (j = 0; j < font->Height; j++) {
			for (i = 0; i < font->Width; i++) {
				if (FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
					if (*ptr & (0x80 >> (i % 8))) {
						//printf("set point x=%d y=%d\r\n",x + i,y + j);
						Paint_SetPixel(x + i, y + j, Color_Foreground);
						// Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
					}
				} else {
					if (*ptr & (0x80 >> (i % 8))) {
						//printf("set point x=%d y=%d\r\n",x + i,y + j);
						Paint_SetPixel(x + i, y + j, Color_Foreground);
						// Paint_DrawPoint(x + i, y + j, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
					} else {
						//printf("set point x=%d y=%d\r\n",x + i,y + j);
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
		DEV_Delay_ms(3000);
	#endif


}
#endif

