/*****************************************************************************
* | File      	:  	epaper_txt.c
* | Author      :   Trauma
* | Function    :   ����txt�ļ������ݴ���
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   
* | Info        :
* -----------------------------------------------------------------------------
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "epaper_txt.h"
#include "fonts.h"
#include "string.h" //memset
#include "Debug.h"
#include "epaper_scream.h"
#include "GUI_Paint.h"


extern s_screen_show g_screen;
extern CH_CN Font16CN_Table[1];
extern cFONT Font16CN;

// ����ȡ���������ݱ��Խ��߶Գ��ˣ����ｫfont_data���ɵľ�����жԽ��߶Գ�
// ����ֿ�û����Ļ������Բ�����һ��
void diag_data(unsigned char *data, unsigned int size)
{
	int i, j;
	unsigned char temp;
	unsigned char buff[CN_FONT_SIZE][CN_FONT_WIDTH] = {0};
	// print_font_data();
	// ת��
	for (i = 0; i < CN_FONT_SIZE; i++)
	{
		for (j = 0; j < CN_FONT_SIZE; j++)
		{
			if (((data[i * 2 + j / SIZE_STEP] >> ((15 - j) % SIZE_STEP)) & 1) > 0)
			{
				buff[i][j] = 1;
				//printf("O");
			}
			else
			{
				buff[i][j] = 0;
				//printf(" ");
			}
		}
		//printf("\n");
	}
	// ת������X����н���
	for (i = 0; i < CN_FONT_SIZE; i++)
	{
		for (j = 0; j < i; j++)
		{
			temp = buff[i][j];
			buff[i][j] = buff[j][i];
			buff[j][i] = temp;
		}
	}
	// ���������
	memset(data, 0, FOAT_BUF_LEN);
	// print_font_data(data);
	// ����
	for (i = 0; i < CN_FONT_SIZE; i++)
	{
		for (j = 0; j < CN_FONT_SIZE; j++)
		{
			data[i * 2 + j / SIZE_STEP] |= buff[i][j] << ((15 - j) % SIZE_STEP);
		}
	}
	// print_font_data(data);
}

void print_font_data(char *font_CN)
{
	for (int i = 0; i < CN_FONT_HEIGHT; i++)
	{
		for (int j = 0; j < CN_FONT_WIDTH; j++)
		{
			int index = i * CN_FONT_WIDTH + j;
			int flag = font_CN[index / SIZE_STEP] & (0x80 >> (index % SIZE_STEP));
			printf("%c", flag > 0 ? 'O' : ' ');
		}
		printf("\n");
	}
}



//��ȡ���Ҵ���Ŀ���ļ������ǲ���ʾ
void TXT_readfile_init(char *filename, s_screen_show *screen_show)
{
	FILE *fp;
	unsigned int txt_lenth, read_lenth;

	// �кź��й���ַ
	unsigned int row = 0, row_cursor = 0;
	unsigned int txt_seek;
	unsigned int fread_size;
	unsigned int page_byte = 0;

	unsigned int ch_pixel_width = 0;
	unsigned int ch_byte_width = 0;

	unsigned int i = 0;
	char world_lenth = 0;
	char line_feed = 0;		// ���б�־λ
	char unable_printf = 0; // ������ʾ�ַ�
	s_page *p_page = NULL;
	
	char txt_buf[512];

	// ��HZK�ļ�
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		perror("Error opening txt file error\r\n");
		exit(1);
	}

	// ��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);
	txt_lenth = ftell(fp);
	printf("file size is : %d\r\n", txt_lenth);

	// ��ʼ��s_page�ṹ��
	// �����ļ���
	strcpy(screen_show->readfilename, filename);
	printf("%s\r\n", screen_show->readfilename);

	// ��ʼ��ҳ������
	screen_show->page_linklist = (s_page *)malloc(sizeof(s_page));
	memset(screen_show->page_linklist, 0, sizeof(s_page));
	p_page = screen_show->page_linklist;

	// ��ʼ��ҳ������������ļ�����Ϊ0�Ļ���page_num��ʼ��Ϊ0������Ϊ1
	if (txt_lenth != 0)
	{
		screen_show->page_num = 1;
	}
	else
	{
		screen_show->page_num = 0;
	}

	p_page->prev = NULL;
	p_page->next = NULL;
	p_page->current_page_id = 0;
	p_page->page_sleek = 0;

	p_page->next = (s_page *)malloc(sizeof(s_page));
	memset(p_page->next, 0, sizeof(s_page));
	p_page->next->prev = p_page;
	p_page->next->current_page_id = p_page->current_page_id + 1;
	p_page->next->page_sleek = txt_seek + i;
	
	// p_pageָ��ָ����һ��Ԫ��
	p_page = p_page->next;

	txt_seek = 0;
	while (txt_seek < txt_lenth)
	{
		if ((txt_seek + 512) <= txt_lenth)
		{
			// û�ж����ļ�ĩβ
			read_lenth = 512;
		}
		else
		{
			// �������ļ�ĩβ
			read_lenth = txt_lenth - txt_seek;
		}

		// �����ļ�ͷ������ȡ��ģ����
		fseek(fp, txt_seek, SEEK_SET);
		fread_size = fread(txt_buf, 1, read_lenth, fp);
		if (fread_size != read_lenth)
		{
			perror("read file error");
		}

		// ���ֿ�ҳ��ȡ�������i�н���ҳ
		if (i != read_lenth)
		{
			i = 1;
		}
		else
		{
			i = 0;
		}
		if(txt_seek == 0)
		{
			i = 0;
		}

		for (; i < read_lenth;)
		{
			// �ж���һ�����ʻ������ĵı߽�
			if (txt_buf[i] <= 0x7F)
			{
				// ascii��
				// ���������⣬���ｫ������Ϊ��һ�������ַ������ɻ���
				line_feed = 0;
				unable_printf = 0;
				for (world_lenth = 0; world_lenth < ASC_MAX_LENTH; world_lenth++)
				{
					if (isalpha(txt_buf[i + world_lenth]) == 0)
					{
						// ����ֻ��ⵥ�ʱ߽����������Ӣ��
						break;
					}
					else
					{
						// ��Ӣ����ĸ
					}
				}

				//������ĸ����
				if (((int)txt_buf[i] - ' ' < 0) || ((int)txt_buf[i] - ' '  > 94 ))
				{
					// ������ʾ�ַ�
					unable_printf = 1;
				}
				// ����Ӣ����ĸ
				// �Իس��������⴦��
				if (txt_buf[i] == '\n')
				{
					// ��������
					line_feed = 1;
				}

				// �ַ���Ⱥ�������
				if (line_feed == 0)
				{
					if(unable_printf == 0)
					{
						// ÿ��Ӣ���ַ������ؿ��ΪASC_PIXEL_WIDTH(11)
						ch_pixel_width = ASC_PIXEL_WIDTH * (world_lenth+1);
						// ÿ��Ӣ���ַ�ռ��1�ֽ�
						ch_byte_width = ASC_BYTE_WIDTH * (world_lenth+1);	
					}
					else if(unable_printf == 1)
					{
						// ÿ��Ӣ���ַ������ؿ��ΪASC_PIXEL_WIDTH(11)
						ch_pixel_width = ASC_PIXEL_WIDTH * (world_lenth);
						// ÿ��Ӣ���ַ�ռ��1�ֽ�
						ch_byte_width = ASC_BYTE_WIDTH * (world_lenth);	
					}
				}
				else if (line_feed == 1)
				{
					// ���з���ռ�ÿռ�Ϊ1
					ch_pixel_width = 0;
					ch_byte_width = ASC_BYTE_WIDTH * (1);
				}
				else
				{
					// ������ʾ�ַ�
					ch_pixel_width = ASC_PIXEL_WIDTH * (1);
					ch_byte_width = ASC_BYTE_WIDTH * (1);
				}
			}
			else
			{
				// ����
				// ÿ�������ַ������ؿ��ΪHZ_PIXEL_WIDTH(16)
				ch_pixel_width = HZ_PIXEL_WIDTH;
				// ÿ�������ַ�ռ��2�ֽ�
				ch_byte_width = HZ_BYTE_WIDTH;
			}

			if ((row_cursor + ch_pixel_width) < screen_show->max_hight - RIGHT_SCREAM_SPACE - LEFT_SCREAM_SPACE * 2 && (line_feed != 1))
			{
				// ���ֲ���Ҫ����
				row_cursor += ch_pixel_width;
				// ƫ�Ƽ�row_cursor
				i += ch_byte_width;
				// ÿ�е��ַ�������row_cursor
				p_page->lines_lenth[row] += ch_byte_width;
				// ҳ��ƫ��
				page_byte += ch_byte_width;
			}
			else
			{
				// ������Ҫ����
				line_feed = 0;
				row_cursor = LEFT_SCREAM_SPACE;
				if (row < TEXT_LINES_NUM)
				{
					// ����û�л�ҳ
					// �кż�1
					row++;
					// �й��λ��ƫ��ch_pixel_width������
					row_cursor += ch_pixel_width;
					// ƫ�Ƽ�row_cursor
					i += ch_byte_width;
					// ÿ�е��ַ�������row_cursor
					p_page->lines_lenth[row] = 0;
					// ÿ�е��ַ�������row_cursor
					p_page->lines_lenth[row] += ch_byte_width;
					// ҳ��ƫ��
					page_byte += ch_byte_width;
				}
				else
				{
					// ���ֻ�ҳ
					p_page->page_lenth = page_byte;

					page_byte = 0;

					screen_show->page_num++;

					//����TXT_readfile_init�����Ƿ���������
					//Test_print_page(p_page, filename);
					// ��Ҫ��ҳ���½�һ��ҳ(p_page)���ҽ���ָ�����
					p_page->next = (s_page *)malloc(sizeof(s_page));
					memset(p_page->next, 0, sizeof(s_page));
					p_page->next->prev = p_page;
					p_page->next->current_page_id = p_page->current_page_id + 1;
					p_page->next->page_sleek = txt_seek + i;

					// p_pageָ��ָ����һ��Ԫ��
					p_page = p_page->next;

					// �к�����Ϊ��0��
					row = 0;
					// �й��λ��ƫ��ch_pixel_width������
					row_cursor += ch_pixel_width;
					// ƫ�Ƽ�row_cursor
					i += ch_byte_width;
					// ÿ�е��ַ�������row_cursor
					p_page->lines_lenth[row] = 0;
					p_page->lines_lenth[row] += ch_byte_width;
				}
			}
		}

		// ��������
		txt_seek += read_lenth;
	}

	// �ر��ļ�
	fclose(fp);
}

void TXT_closefile(s_screen_show *screen_show)
{
	s_page *p;
	s_page *p_next;
	int i = 0 ;

	p = screen_show->page_linklist;
	p_next = screen_show->page_linklist->next;

	//ɾ����Ļ��ʾ������
	free(screen_show->BlackImage);

	//ɾ������
	while(p!=NULL)
	{
        p_next = p->next; // ������һ���ڵ�ĵ�ַ
        free(p); // �ͷŵ�ǰ�ڵ���ڴ�
        p = p_next; // �ƶ�����һ���ڵ�
        i++;
	}
	printf("recycle file page = %d \r\n", i);

}
