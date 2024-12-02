
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "epaper_txt.h"
#include "fonts.h"
#include "string.h" //memset
#include "Debug.h"
#include "epaper_scream.h"
#include "GUI_Paint.h"

extern s_scream_show g_scream;

static char txt_buf[512];

// 中文配置接口，只包括16*16字模，其他字模还没有尝试过
CH_CN Font16CN_Table[1] = {0};

cFONT Font16CN =
{
		Font16CN_Table,
		sizeof(Font16CN_Table) / sizeof(CH_CN), /*size of table*/
		16,										/* ASCII Width */
		CN_FONT_WIDTH,							/* Width */
		CN_FONT_SIZE,							/* Height */
};

// 字符的字模数据，这里需要根据实际的HZK16文件填充
unsigned char font_data[FOAT_BUF_LEN];

// 发现取出来的数据被对角线对称了，这里将font_data构成的矩阵进行对角线对称
// 如果字库没问题的话，可以不用这一步
void diag_data(unsigned char *data, unsigned int size)
{
	int i, j;
	unsigned char temp;
	unsigned char buff[CN_FONT_SIZE][CN_FONT_WIDTH] = {0};
	// print_font_data();
	// 转储
	for (i = 0; i < CN_FONT_SIZE; i++)
	{
		for (j = 0; j < CN_FONT_SIZE; j++)
		{
			if (((data[i * 2 + j / SIZE_STEP] >> ((15 - j) % SIZE_STEP)) & 1) > 0)
			{
				buff[i][j] = 1;
				// Debug("O");
			}
			else
			{
				buff[i][j] = 0;
				// Debug(" ");
			}
		}
		// Debug("\n");
	}
	// 转换，对X轴进行交换
	for (i = 0; i < CN_FONT_SIZE; i++)
	{
		for (j = 0; j < i; j++)
		{
			temp = buff[i][j];
			buff[i][j] = buff[j][i];
			buff[j][i] = temp;
		}
	}
	// 将数组清除
	memset(data, 0, FOAT_BUF_LEN);
	// print_font_data(data);
	// 回填
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

void test_chinese_byte()
{
	char HZ_test[] = "1: \r 2:\n";
	printf("%s", HZ_test);
	printf("end");
	return 0;
}

// 读取中文字体
void TXT_read_font_CN(const char *char_code, char *font_CN, int font_size)
{
	FILE *fp;
	long offset;
	int t1, t2;
	int sizeof_byte = SIZE_STEP;
	int offset_step = CN_FONT_WIDTH * CN_FONT_HEIGHT / sizeof_byte;
	int fread_size = 0;

	// 打开HZK文件
	fp = fopen("HZK16", "rb");
	if (fp == NULL)
	{
		perror("Error opening font file");
		exit(1);
	}

	// 读取GB2312编码的汉字
	unsigned char incode[GB2312_CODE_SIZE];
	memcpy(incode, char_code, GB2312_CODE_SIZE);

	// 计算偏移量
	t1 = incode[0];
	t2 = incode[1];
	if (t1 > 0xa0)
	{
		offset = ((t1 - 0xa1) * 94 + (t2 - 0xa1)) * offset_step;
	}
	else
	{
		offset = (t1 + 156 - 1) * offset_step;
	}

	// 跳过文件头部，读取字模数据
	fseek(fp, offset, SEEK_SET);
	fread_size = fread(font_data, sizeof_byte, CN_FONT_WIDTH * CN_FONT_HEIGHT / sizeof_byte, fp);

	if (fread_size <= 0)
	{
		// 读取中文失败
		Debug("read CN file error,code is :%s\r\n", incode);
	}

	fclose(fp);

	// Debug("CH size = %d\r\n",fread_size);

	diag_data(font_data, FOAT_BUF_LEN);

	memcpy(font_CN, font_data, CN_FONT_WIDTH * CN_FONT_HEIGHT / sizeof_byte);
}

void TXT_readfile_init(char *filename, s_scream_show *scream_show)
{
	FILE *fp;
	unsigned int txt_lenth, read_lenth;

	// 行号和行光标地址
	unsigned int row = 0, row_cursor = 0;
	unsigned int txt_seek;
	unsigned int fread_size;
	unsigned int page_byte = 0;
	char filename_lenth;

	unsigned char is_asc = 0;
	unsigned int ch_pixel_width = 0;
	unsigned int ch_byte_width = 0;

	unsigned int i = 0;
	char world_lenth = 0;
	char line_feed = 0;		// 换行标志位
	char unable_printf = 0; // 不可显示字符
	s_page *p_page = NULL;

	// 打开HZK文件
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		perror("Error opening txt file error\r\n");
		exit(1);
	}

	// 读取文件长度
	fseek(fp, 0, SEEK_END);
	txt_lenth = ftell(fp);
	printf("file size is : %d\r\n", txt_lenth);

	// 初始化s_page结构体
	// 复制文件名
	strcpy(scream_show->readfilename, filename);
	printf("%s\r\n", scream_show->readfilename);

	// 初始化页面链表
	scream_show->page_linklist = (s_page *)malloc(sizeof(s_page));
	memset(scream_show->page_linklist, 0, sizeof(s_page));
	p_page = scream_show->page_linklist;

	// 初始化页面总数，如果文件长度为0的话，page_num初始化为0，否则为1
	if (txt_lenth != 0)
	{
		scream_show->page_num = 1;
	}
	else
	{
		scream_show->page_num = 0;
	}

	p_page->prev = NULL;
	p_page->next = NULL;
	p_page->current_page_id = 0;
	p_page->page_sleek = 0;

	txt_seek = 0;
	while (txt_seek < txt_lenth)
	{
		if ((txt_seek + 512) <= txt_lenth)
		{
			// 没有读到文件末尾
			read_lenth = 512;
		}
		else
		{
			// 读到了文件末尾
			read_lenth = txt_lenth - txt_seek;
		}

		// 跳过文件头部，读取字模数据
		fseek(fp, txt_seek, SEEK_SET);
		fread_size = fread(txt_buf, 1, read_lenth, fp);
		if (fread_size != read_lenth)
		{
			perror("read file error");
		}

		// 汉字跨页读取，这里的i承接上页
		if (i == read_lenth)
		{
			i = 1;
		}
		else
		{
			i = 0;
		}
		for (; i < read_lenth;)
		{
			// 判断下一个单词或者中文的边界
			if (txt_buf[i] <= 0x7F)
			{
				// ascii码
				// 处理单词问题，这里将单词认为是一个完整字符，不可换行
				line_feed = 0;
				unable_printf = 0;
				is_asc = 1;
				for (world_lenth = 0; world_lenth < ASC_MAX_LENTH; world_lenth++)
				{
					if (isalpha(txt_buf[i + world_lenth]) == 0)
					{
						// 这里只检测单词边界在哪里
						break;
					}
					else
					{
						// 是英文字母
					}
				}

				//不在字母表当中
				if ((txt_buf[i] - ' ' < 0) && (txt_buf[i] - ' '  > 94 ))
				{
					// 不可显示字符
					unable_printf = 1;
				}
				// 不是英文字母
				// 对回车换行特殊处理
				if (txt_buf[i] == '\n')
				{
					// 发生换行
					line_feed = 1;
				}

				// 字符宽度后续处理
				if (line_feed == 0)
				{
					if(unable_printf == 0)
					{
						// 每个英文字符的像素宽度为ASC_PIXEL_WIDTH(11)
						ch_pixel_width = ASC_PIXEL_WIDTH * (world_lenth+1);
						// 每个英文字符占用1字节
						ch_byte_width = ASC_BYTE_WIDTH * (world_lenth+1);	
					}
					else if(unable_printf == 1)
					{
						// 每个英文字符的像素宽度为ASC_PIXEL_WIDTH(11)
						ch_pixel_width = ASC_PIXEL_WIDTH * (world_lenth);
						// 每个英文字符占用1字节
						ch_byte_width = ASC_BYTE_WIDTH * (world_lenth);	
					}
				}
				else if (line_feed == 1)
				{
					ch_pixel_width = 0;
					// 换行符号占用空间为1
					ch_byte_width = ASC_BYTE_WIDTH * (1);
				}
				else
				{
					ch_pixel_width = ASC_PIXEL_WIDTH * (1);
					// 不可显示字符
					ch_byte_width = ASC_BYTE_WIDTH * (1);
				}
			}
			else
			{
				// 中文
				is_asc = 0;
				// 每个中文字符的像素宽度为HZ_PIXEL_WIDTH(16)
				ch_pixel_width = HZ_PIXEL_WIDTH;
				// 每个中文字符占用2字节
				ch_byte_width = HZ_BYTE_WIDTH;
			}

			if ((row_cursor + ch_pixel_width) < scream_show->max_hight - RIGHT_SCREAM_SPACE - LEFT_SCREAM_SPACE * 2 && (line_feed != 1))
			{
				// 文字不需要换行
				row_cursor += ch_pixel_width;
				// 偏移加row_cursor
				i += ch_byte_width;
				// 每行的字符数量加row_cursor
				p_page->lines_lenth[row] += ch_byte_width;
				// 页内偏移
				page_byte += ch_byte_width;
			}
			else
			{
				// 文字需要换行
				line_feed = 0;
				row_cursor = LEFT_SCREAM_SPACE;
				if (row < TEXT_LINES_NUM)
				{
					// 文字没有换页
					// 行号加1
					row++;
					// 行光标位置偏移ch_pixel_width个像素
					row_cursor += ch_pixel_width;
					// 偏移加row_cursor
					i += ch_byte_width;
					// 每行的字符数量加row_cursor
					p_page->lines_lenth[row] = 0;
					// 每行的字符数量加row_cursor
					p_page->lines_lenth[row] += ch_byte_width;
					// 页内偏移
					page_byte += ch_byte_width;
				}
				else
				{
					// 文字换页
					p_page->page_lenth = page_byte;

					page_byte = 0;

					scream_show->page_num++;

					Test_print_page(p_page, filename);
					// 需要换页，新建一个页(p_page)并且进行指针操作
					p_page->next = (s_page *)malloc(sizeof(s_page));
					memset(p_page->next, 0, sizeof(s_page));
					p_page->next->prev = p_page;
					p_page->next->current_page_id = p_page->current_page_id + 1;
					p_page->next->page_sleek = txt_seek + i;

					// p_page指针指向下一个元素
					p_page = p_page->next;

					// 行号设置为第0行
					row = 0;
					// 行光标位置偏移ch_pixel_width个像素
					row_cursor += ch_pixel_width;
					// 偏移加row_cursor
					i += ch_byte_width;
					// 每行的字符数量加row_cursor
					p_page->lines_lenth[row] = 0;
					p_page->lines_lenth[row] += ch_byte_width;
				}
			}
		}

		// 后续处理
		txt_seek += read_lenth;
	}

	Test_print_page(p_page, filename);

	// 关闭文件
	fclose(fp);
}

void TXT_closefile(s_scream_show *scream_show)
{
	scream_show->page_linklist;
}