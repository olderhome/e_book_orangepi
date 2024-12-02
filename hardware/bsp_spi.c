#include "bsp_spi.h"


s_spi g_spi0;


void SPI_struct_init()
{
	g_spi0.channel = SPI0_CHANNLE;
	g_spi0.speed = SPI0_SPEED;

}

