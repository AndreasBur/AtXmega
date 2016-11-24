#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
	extern "C" {
#endif


/*************************************************************************************************************************************
*   I N C L U D E
*************************************************************************************************************************************/
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <termios.h>
#include <string.h>
#include "fonts.h"
#include "qdbmp.h"
//Fonts
#include "6x8_horizontal_LSB_1.h"
#include "8x14_horizontal_LSB_1.h"
#include "12x16_horizontal_LSB_1.h"
#include "16x26_horizontal_LSB_1.h"


/*************************************************************************************************************************************
*   D E F I N E S
*************************************************************************************************************************************/
#define GLCD_WIDTH				320
#define GLCD_HEIGHT				240

#define FONT_ORIGIN_HEIGHT      16
#define FONT_ORIGIN_WIDTH       8
#define FONT_SMALL_HEIGHT       5
#define FONT_SMALL_WIDTH        6
#define FONT_NORMAL_HEIGHT      14
#define FONT_NORMAL_WIDTH       8
#define FONT_BIG_HEIGHT         16
#define FONT_BIG_WIDTH          12
#define FONT_EXTREME_BIG_HEIGHT 26
#define FONT_EXTREME_BIG_WIDTH  16

#define DIST_TEXT_BORDER    4 // EVTL WOANDERS HIN

/*************************************************************************************************************************************
*   T Y P E D E F
*************************************************************************************************************************************/
typedef enum {
    COLOR_NONE=0x10000,
    COLOR_WHITE=0xFFFF,
    COLOR_BLACK=0x0000,
    COLOR_GREY=0xF7DE,
    COLOR_BLUE1=0x001F,
    COLOR_BLUE2=0x051F,
    COLOR_RED=0xF800,
    COLOR_MAGENTA=0xF81F,
    COLOR_GREEN=0x07E0,
    COLOR_CYAN=0x7FFF,
    COLOR_YELLOW=0xFFE0
} color_t;

typedef enum {
    FONT_NONE,
    FONT_ORIGIN,
    FONT_SMALL,
    FONT_NORMAL,
    FONT_BIG,
    FONT_EXTREME_BIG
} font_t;

typedef enum {
	BORDER_NONE,
	BORDER_RECT,
	BORDER_RECT_ROUNDED,
	BORDER_CIRCLE
} border_t;

typedef enum {
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_CENTER
} align_t;

//#define  ASCII_8X16_MS_Gothic
#define  ASCII_8X16_System

#define RGB565CONVERT(red, green, blue)\
(unsigned short)( (( red   >> 3 ) << 11 ) | \
(( green >> 2 ) << 5  ) | \
( blue  >> 3 ))


/*************************************************************************************************************************************
*   P R O T O T Y P E S
*************************************************************************************************************************************/
void GLCD_Init(int argc, char *argv[]);
void LCD_Init(const char*);
void LCD_Clear(color_t);
void LCD_SetPoint(unsigned short, unsigned short, color_t);
int LCD_PutImage(unsigned short x, unsigned short y, short maxwidth, short maxheight, const char* file);
void PutChar(unsigned short Xpos, unsigned short Ypos, unsigned char ascii, color_t charColor, color_t bkColor, font_t font);
void GetASCIICode(unsigned char*,unsigned char);
int GetFontHeight(font_t font);
int GetFontWidth(font_t font);
int GetCenterTextX(const char* text, font_t font, int width, int offset);
int GetCenterTextY(font_t font, int height, int offset);
int sgn(int);
//int abs(int n);
void LCD_Text(unsigned short Xpos, unsigned short Ypos, const char *str, color_t Color, color_t bkColor, font_t font);
void LCD_DrawLine(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, color_t col);
void LCD_DrawBox(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, color_t backgroundcol, border_t border, unsigned short borderwidth, color_t bordercol);
void drawCirclePart(unsigned short xc, unsigned short yc, unsigned short x, unsigned short y, color_t col);
void drawCircle(unsigned short xc, unsigned short yc, unsigned short r, color_t col);
void LCD_DrawCircle(unsigned short xc, unsigned short yc, unsigned short r, color_t backgroundcol, unsigned short borderwidth, color_t bordercol);
void LCD_DrawCircleFill(unsigned short x, unsigned short y, unsigned short r, color_t bcol, color_t col);

#ifdef __cplusplus
    }
#endif
#endif
