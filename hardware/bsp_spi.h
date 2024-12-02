#ifndef __BSP_SPI_H_
#define __BSP_SPI_H_


#define SPI0_CHANNLE	0
#define SPI0_SPEED		10*1000*1000


typedef struct
{
	int channel;
	int speed;
}s_spi; 

void SPI_struct_init();


#endif



