/*****************************************************************************
* | File      	:  	epaper_scream.c
* | Author      :   Trauma
* | Function    :   �����������ʾ
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
s_page *p_page =  NULL;



void Screen_DEV_Init()
{

	//GPIO��ʼ��
	DEV_GPIO_Init();
	//SPI��ʼ��
	DEV_SPI_Init();
	//e_paper�����ʼ��
	DEV_Module_Init();

}


void Screen_init()
{

	//e_paperϵͳ��ʼ��
	EPD_2IN9_V2_Init();
	//e_paper����
	EPD_2IN9_V2_Clear();
	DEV_Delay_ms(1000);
	
	//Create a new image cache 
	g_screen.Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
	g_screen.max_width = EPD_2IN9_V2_WIDTH;
	g_screen.max_hight = EPD_2IN9_V2_HEIGHT;

	if((g_screen.BlackImage = (UBYTE *)malloc(g_screen.Imagesize)) == NULL) 
	{
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
	Paint_DrawString(10, 10, "ʫԻ��", &Font16CN , &Font16, WHITE, BLACK);
	Paint_DrawString(10, 30, "����δ������ң�ãã�������˼���", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 50, "�Դ��̹��ƺ��ɣ����ٴ������Ǳ档", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 70, "����Ⱥ�������ʣ���������Գ��ơ�", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 90, "��֪�컯��Ԫ�����뿴�����Ͷ򴫡�", &Font16CN, &Font16, WHITE, BLACK);
	//Paint_DrawString(10, 110, "hello world", &Font12,BLACK , WHITE);
	Paint_DrawString(10, 110,"���Trauma���", &Font16CN,&Font16, WHITE, BLACK);

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
	Paint_DrawString(10, 10, "ʫԻ��", &Font16CN , &Font16, WHITE, BLACK);
	Paint_DrawString(10, 30, "����δ������ң�ãã�������˼���", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 50, "�Դ��̹��ƺ��ɣ����ٴ������Ǳ档", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 70, "����Ⱥ�������ʣ���������Գ��ơ�", &Font16CN, &Font16, WHITE, BLACK);
	Paint_DrawString(10, 90, "��֪�컯��Ԫ�����뿴�����Ͷ򴫡�", &Font16CN, &Font16, WHITE, BLACK);
	//Paint_DrawString(10, 110, "hello world", &Font12,BLACK , WHITE);
	Paint_DrawString(10, 110,"���Trauma���", &Font16CN,&Font16, WHITE, BLACK);
	//Paint_DrawString(10, 110, "123456789ABCDEFGHIJKLMN���", &Font16CN, &Font16, WHITE, BLACK);

	#if 0
	cFONT* font = &Font16CN;
	UWORD Color_Foreground = WHITE;
	UWORD Color_Background = BLACK;
	char* ptr = font->table[0].matrix;
	x = 130;
	y = 20;

	//TXT_read_font_CN("��",ptr, 16);


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
 * ��ȡ��ǩ��Ϣ
 * 
 * @param mark ָ��s_mark�ṹ���ָ�룬���ڴ洢��ȡ����ǩ��Ϣ
 * @param filename Ҫ���ҵ���ǩ��Ӧ���ļ���
 * @return �ɹ�����0�����û���ҵ�����ǩ����-2������ļ������ڷ���-1
 */

int Config_mark_read(s_mark *mark, char *filename) 
{
	s_mark read_mark;
    FILE *file = fopen(MARK_FILE, "r");
    if (file == NULL) 
	{
		Debug("do not found mark file\n");
        return -1; // �ļ�������
    }

    while (fread(&read_mark, sizeof(s_mark), 1, file)) 
	{
        if (strcmp(read_mark.file_name, filename) == 0) 
		{
            fclose(file);
			Debug("founded mark\n");
			memcpy(mark,&read_mark,sizeof(s_mark));
            return 0; // �ҵ���ǩ
        }
    }

    fclose(file);
	Debug("do not found mark\n");
    return -2; // û���ҵ�����ǩ
}
/**
 * д����ǩ��Ϣ
 * 
 * @param mark ָ��s_mark�ṹ���ָ�룬����Ҫд�����ǩ��Ϣ
 * @return �ɹ�����0��������ֶ�д���󷵻�-2
 */

int Config_mark_write(s_mark *mark) 
{
    FILE *file = fopen(MARK_FILE, "a");
    if (file == NULL) 
	{
        file = fopen(MARK_FILE, "w"); // ����ļ������ڣ��򴴽��ļ�
        if (file == NULL) 
		{
			Debug("build mark file failed\n");
            return -2; // �ļ�����ʧ��
        }
    } 
	else 
	{
        s_mark temp;
        while (fread(&temp, sizeof(s_mark), 1, file)) 
		{
            if (strcmp(temp.file_name, mark->file_name) == 0) 
			{
				Debug("clean old mark\n");
                // �ҵ�����ǩ��ɾ����
                fseek(file, -sizeof(s_mark), SEEK_CUR);
                fwrite(&temp, sizeof(s_mark), 1, file); // д����ʱ���������ǵ�ԭ��ǩ
                fseek(file, sizeof(s_mark), SEEK_CUR);
                break;
            }
        }
    }

	Debug("save new mark\n");
    // д������ǩ
    fseek(file, 0, SEEK_END); // �ƶ����ļ�ĩβ
    fwrite(mark, sizeof(s_mark), 1, file);
    fclose(file);
    return 0; // д��ɹ�
}

/**
 * ���ָ���ļ�������ǩ��Ϣ
 * 
 * @param filename Ҫ�������ǩ��Ӧ���ļ���
 */

void Config_mark_clean(char *filename) 
{
    FILE *file = fopen(MARK_FILE, "r+");
    if (file == NULL) 
	{
        return; // �ļ������ڣ��������
    }

    s_mark temp;
    int found = 0;
    while (fread(&temp, sizeof(s_mark), 1, file)) 
	{
        if (strcmp(temp.file_name, filename) == 0) 
		{
            found = 1;
            continue; // ��������ǩ
        }
        fwrite(&temp, sizeof(s_mark), 1, file); // д���Ŀ����ǩ
    }

    if (found) 
	{
        fseek(file, -sizeof(s_mark), SEEK_CUR); // ����ҵ�����ǩ���ص����һ����Ŀ����ǩ��λ��
        fwrite(&temp, sizeof(s_mark), 1, file); // ���ǵ����һ����Ŀ����ǩ��ʵ��������������һ����ǩ��λ��
    }

    fclose(file);
}


/**
 * @brief ��ӡ��Ļҳ������
 * 
 * �ú������ڸ����ṩ����Ļ�����ҳ����룬��ӡ��ǰҳ������ݡ�
 * ��֧�ַ�ҳ���ܣ�����ͨ�������acode���������Ʒ�����һҳ��'n'������һҳ��'p'����
 * 
 * @param screen ָ����Ļ��ʾ�����ָ��
 * @param acode ���Ʒ�ҳ�Ͷ�ȡҳ���ж����ַ���
 				'n'��ʾ��һҳ��'p'��ʾ��һҳ��'r'��ʾת����ǩ��'w'��ʾ������ǩ��
 */
void Screen_print_page(const s_screen_show *screen,char *acode)
{
	s_page *p_frist_page = screen->page_linklist;
	
	unsigned int i = 0;
	unsigned int auto_transpage = 0;
	char fread_buf[40] = {0};
	unsigned int page_seek = 0;
	FILE *fp;
	s_mark mark = {0};

	//��ʼ��p_page
	if(p_page == NULL)
	{
		p_page = screen->page_linklist;
	}
	
	//next ��һҳ
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
	//prev ��һҳ
	else if(acode[0] == 'p')
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
	//mark ��¼��ǩ
	else if(acode[0] == 'm')
	{
		mark.mark_id = 0;
		strcpy(mark.file_name,screen->readfilename);
		mark.page_id = p_page->current_page_id;
		Config_mark_write(&mark);
	}
	//transfer ת�Ƶ���ǩ
	else if(acode[0] == 't')
	{
		
		Config_mark_read(&mark,screen->readfilename);
		p_page = p_frist_page;
		for(i = 0 ; i < screen->page_num ; i++)
		{
			p_page = p_frist_page;
			while(p_page->current_page_id < mark.page_id)
			{
				p_page = p_page->next;
			}
		}
			
	}

	//run �Զ���ҳ
	else if(acode[0] == 'r')
	{
		auto_transpage = 1;
	}
	//ֹͣ�Զ���ҳ
	else 
	{
		auto_transpage = 0;
	}

	do
	{

		page_seek = p_page->page_sleek;

		fp = fopen(screen->readfilename, "rb");
		memset(screen->BlackImage , 0 ,screen->Imagesize);

		sprintf(fread_buf,"page %d/%d",p_page->current_page_id,screen->page_num);
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

		//�ر��ļ�
		fclose(fp);

		//��ʱ
		if(auto_transpage == 0)
		{
			//sleep(2);
		}
		else
		{
			sleep(10);
		}
		
	}
	while(auto_transpage == 1);
}


//���һ������
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
	//�ر��ļ�
	fclose(fp);
	sleep(5);
}

//��ʼ��s_scream_show
void s_scream_show_init(s_screen_show *screen)
{
	memset(screen , 0 ,sizeof(screen));
}


//ѡ���ļ�
void Screen_select_file()
{

}


