#ifndef __EPAPER_TXT
#define __EPAPER_TXT




#include "epaper_scream.h"
#include "EPD_2in9_V2.h"



void diag_data(unsigned char *data, unsigned int size);
void print_font_data(char *font_CN);
void TXT_readfile_init(char * filename ,s_screen_show* screen_show);
void TXT_closefile(s_screen_show *screen_show);

#endif