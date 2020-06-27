/**
  ******************************************************************************
  * @file           : st7789.h
  * @brief          : 阿里云aliosthings提取的文件
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

#ifndef __ST7789_H
#define __ST7789_H

#define WIDTH		240
#define HEIGHT		240
#define BPP		16

#include "stm32l4xx_hal.h"

/* Init script function */
struct st7789_function {
  uint8_t cmd;
  uint16_t data;
};

/* Init script commands */
enum st7789_cmd {
  ST7789_START,
  ST7789_END,
  ST7789_CMD,
  ST7789_DATA,
  ST7789_DELAY
};

/* ST7789 Commands */
#define ST7789_CASET	0x2A
#define ST7789_RASET	0x2B
#define ST7789_RAMWR	0x2C
#define ST7789_RAMRD	0x2E

void st7789_init(void);//这玩意非常重要，必须初始化
void LcdWriteReg(uint8_t Data);//向ST7789发送命令，手册里应该有
void LcdWriteData(uint8_t Data);//向ST7789发送数据
void LcdWriteDataMultiple(uint8_t * pData, int NumItems);//向ST7789发送多个数据

void ST7789H2_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);//向ST7789发送一个像素数据
void ST7789H2_WriteLine(uint16_t Xpos, uint16_t Ypos, uint16_t *RGBCode, uint16_t pointNum);//向ST7789发送一行像素数据
/*测试用*/
void st7789_display_picture(void);//黑靛蓝白
void BSP_LCD_Clear(void);//全黑
/*我增加的*/
void lcd_draw_char(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t fcolor);//阿里云aliosthings迁移的
void lcd_draw_str(uint16_t x, uint16_t y, char *str, uint8_t size, uint16_t color, int8_t new_line);//阿里云aliosthings迁移的
void st7789_display_background(void);//不如BSP_LCD_Clear(void);//全黑
#endif /* __ST7789_H */
