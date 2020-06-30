#ifndef __SPI1_H
#define __SPI1_H

#include "stm32l4xx.h"

void SPI1_Init(void);
unsigned char SPI1_ReadWriteByte(unsigned char TxData);
unsigned char SPI1_WriteData(unsigned char *TxData,unsigned short size);


#endif




