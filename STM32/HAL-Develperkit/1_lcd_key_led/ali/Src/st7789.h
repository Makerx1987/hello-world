/**
  ******************************************************************************
  * @file           : st7789.h
  * @brief          : ������aliosthings��ȡ���ļ�
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

void st7789_init(void);//������ǳ���Ҫ�������ʼ��
void LcdWriteReg(uint8_t Data);//��ST7789��������ֲ���Ӧ����
void LcdWriteData(uint8_t Data);//��ST7789��������
void LcdWriteDataMultiple(uint8_t * pData, int NumItems);//��ST7789���Ͷ������

void ST7789H2_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);//��ST7789����һ����������
void ST7789H2_WriteLine(uint16_t Xpos, uint16_t Ypos, uint16_t *RGBCode, uint16_t pointNum);//��ST7789����һ����������
/*������*/
void st7789_display_picture(void);//�ڵ�����
void BSP_LCD_Clear(void);//ȫ��
/*�����ӵ�*/
void lcd_draw_char(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t fcolor);//������aliosthingsǨ�Ƶ�
void lcd_draw_str(uint16_t x, uint16_t y, char *str, uint8_t size, uint16_t color, int8_t new_line);//������aliosthingsǨ�Ƶ�
void st7789_display_background(void);//����BSP_LCD_Clear(void);//ȫ��
#endif /* __ST7789_H */
