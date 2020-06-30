#include "stm32l4xx_hal.h"
#include "st7789.h"
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "fontlib.h"

uint32_t width = 240;
uint32_t height = 240;

void lcd_draw_char(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t fcolor)
{
		uint8_t i            = 0;
    uint8_t j            = 0;
    uint8_t temp         = 0;
//    uint16_t write_count = 0;
    uint16_t xtemp       = x;
    uint16_t ytemp       = y;
//    uint8_t csize        = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
    uint8_t char_len     = 0;
    uint8_t *pos         = NULL;
    num                  = num - ' ';
    if (12 == size) {
        pos      = (uint8_t *)&g_asc2_1206[num];
        char_len = 12;
    } else if (16 == size) {
        pos      = (uint8_t *)&g_asc2_1608[num];
        char_len = 16;
    } else if (24 == size) {
        pos      = (uint8_t *)&g_asc2_2412[num];
        char_len = 36;
    } else if (36 == size) {
        pos      = (uint8_t *)&g_asc2_3636[num];
        char_len = 90;
    } else {
        return ;
    }
    for (i = 0; i < char_len; ++i) {
        temp = *pos++;
        for (j = 0; j < 8; ++j) {
            if (temp & 0x80) {
                 ST7789H2_WritePixel(xtemp, ytemp, fcolor);
            }
            temp <<= 1;
            ytemp += 1;
            if (size == (ytemp - y)) {
                ytemp = y;
                xtemp += 1;
                break;
            }
        }
    }
}
void lcd_draw_str(uint16_t x, uint16_t y, char *str, uint8_t size, uint16_t color, int8_t new_line)
{
	  uint16_t xstart = x;
    uint16_t ystart = y;
    uint16_t xres   = 0;
    uint16_t yres   = 0;
//    if (NULL == g_lcd) {
//        return (-1);
//    }
    xres = width;
    yres = height;
    while ((*str <= '~') && (*str >= ' ')) {
        if (new_line) {
            if (xstart > xres) {
                xstart = x;
                ystart += size;
            }
            if (ystart > yres) {
                break;
            }
        }
        lcd_draw_char(xstart, ystart, *str, size, color);
        xstart += size / 2;
        str += 1;
    }
}

