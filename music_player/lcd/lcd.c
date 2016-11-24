/*******************************************************************************
* Function Name  : lcd
* Description    : Driver for LCD HY28A-LCDB using:
*                  ILI9320 for LCD & ADS7843 for Touch Panel
				   https://github.com/topogigio/HY28A-LCDB-GUIFB
* Input          : None
* Output         : None
* Return         : None
* Execute        : sudo ./fblcd /dev/fbX /dev/input/eventX
*******************************************************************************/

#include "lcd.h"

/*************************************************************************************************************************************
*   G L O B A L   V A R I A B L E S
*************************************************************************************************************************************/
struct fb_var_screeninfo vinfo;
struct fb_var_screeninfo orig_vinfo;
struct fb_fix_screeninfo finfo;
char *fbp = NULL;
int fbfd = 0;
long int screensize = 0;


/*******************************************************************************
* Function Name  : GLCD_Init
* Description    : Init of the LCD and TP
* Input          : arguments and number of arguments
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void GLCD_Init(int argc, char *argv[])
{
	if (argc < 3) {
			printf("Usage: [/dev/fbX] [/dev/input/eventX]\n");
			//exit(1);
		}

		LCD_Init(argv[1]);

		if ((int)fbp == -1) {
			printf("Failed to mmap\n");
		} else {
			LCD_Clear(COLOR_WHITE);
		}
}


/*******************************************************************************
* Function Name  : LCD_Init
* Description    : Initialize TFT Controller.
* Input          : /dev/fbX
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_Init(const char* frameb)
{
    // Open the file for reading and writing
    fbfd = open(frameb, O_RDWR);
    if (!fbfd) {
        printf("Error: cannot open framebuffer device\n");
        //exit(1);
    }
    printf("The framebuffer/pointing device was opened successfully\n");

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading variable information\n");
    }
    printf("Original %dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );

    // Store for reset (copy vinfo to vinfo_orig)
    memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("Error reading fixed information.\n");
    }

    // map fb to user mem
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    fbp = (char*)mmap(0,
              screensize,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fbfd,
              0);
}


/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Fill the screen as the specified color
* Input          : - Color: Screen Color
* Output         : None
* Return         : None
* Attention	 	 : None
*******************************************************************************/
void LCD_Clear(color_t Color)
{
    memset((unsigned short*)fbp, Color, vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8);
}


/******************************************************************************
* Function Name  : LCD_SetPoint
* Description    : Drawn at a specified point coordinates
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate
*          		   - Color: background color
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_SetPoint( unsigned short Xpos, unsigned short Ypos, color_t Color)
{
    if( Xpos >= vinfo.xres || Ypos >= vinfo.yres ) return;
    // calculate the pixel's byte offset inside the buffer
    // note: x * 2 as every pixel is 2 consecutive bytes
    unsigned int pix_offset = Xpos * 2 + Ypos * finfo.line_length;
    // now this is about the same as 'fbp[pix_offset] = value'
    // but a bit more complicated for RGB565
    //unsigned short c = ((r / 8) << 11) + ((g / 4) << 5) + (b / 8);
    //unsigned short c = ((r / 8) * 2048) + ((g / 4) * 32) + (b / 8);
    // write 'two bytes at once'
    //*((unsigned short*)(fbp + pix_offset)) = c;
    *((unsigned short*)(fbp + pix_offset)) = Color;
}


/******************************************************************************
* Function Name  : PutChar
* Description    : Lcd screen displays a character
* Input          :  - Xpos: Horizontal coordinate
*                   - Ypos: Vertical coordinate
*				    - ASCI: Displayed character
*				    - charColor: Character color
*				    - bkColor: Background color
                    - font: text font
* Output         : None
* Return         : None
* Attention	 	 : None
*******************************************************************************/
void PutChar(unsigned short Xpos, unsigned short Ypos, unsigned char ascii, color_t charColor, color_t bkColor, font_t font)
{
    unsigned short i, j;
    unsigned char buffer[16], tmp_char;

	unsigned char x,y,w,a=0;

	if(font == FONT_ORIGIN)
	{
		GetASCIICode(buffer,ascii);  // get font data
		for( i=0; i<16; i++ )
		{
			tmp_char = buffer[i];
			for( j=0; j<8; j++ )
			{
				if( ((tmp_char >> (7 - j)) & 0x01) == 0x01 )
				{
					LCD_SetPoint( Xpos + j, Ypos + i, charColor ); // Character color
				}
				else
				{
					if (bkColor != COLOR_NONE) LCD_SetPoint( Xpos + j, Ypos + i, bkColor );   // Background color
				}
			}
		}
		return;
	}


	switch(ascii)
	{
		case 188: // ü
			ascii = 129;
			break;
		case 156: // Ü
			ascii = 154;
			break;
		case 182: // ö
			ascii = 148;
			break;
		case 150: // Ö
			ascii = 153;
			break;
		case 164: // ä
			ascii = 132;
			break;
		case 132: // Ä
			ascii = 142;
			break;
		case 180: // ´
			ascii = 239;
		default:
			break;
	}

	if(font == FONT_SMALL)
	{
		for (y=0; y<8; y++)
		{
			w=font6x8[ascii][y];
			w=w>>2;
			for (x=0; x<6; x++)
			{
				if (w&1) LCD_SetPoint( Xpos + x, Ypos + y, charColor );
				else if(bkColor != COLOR_NONE) LCD_SetPoint( Xpos + x, Ypos + y, bkColor );
				w=w>>1;
			}
		}
	}

	if(font == FONT_NORMAL)
	{
		for (y=0; y<14; y++)
		{
			w=font8x14[ascii][y];
			for (x=0; x<8; x++)
			{
				if (w&1) LCD_SetPoint( Xpos + x, Ypos + y, charColor );
				else if(bkColor != COLOR_NONE) LCD_SetPoint( Xpos + x, Ypos + y, bkColor );
				w=w>>1;
			}
		}
	}

	if(font == FONT_BIG)
	{
		for (y=0; y<16; y++)
		{
			w=font12x16[ascii][a+1];
			w=w>>4;
			for (x=0; x<4; x++)
			{
				if (w&1) LCD_SetPoint( Xpos + x, Ypos + y, charColor );
				else if(bkColor != COLOR_NONE) LCD_SetPoint( Xpos + x, Ypos + y, bkColor );
				w=w>>1;
			}

			w=font12x16[ascii][a];
			for (x=4; x<12; x++)
			{
				if (w&1) LCD_SetPoint( Xpos + x, Ypos + y, charColor );
				else if(bkColor != COLOR_NONE) LCD_SetPoint( Xpos + x, Ypos + y, bkColor );
				w=w>>1;
			}
			a+=2;
		}
	}

	if(font == FONT_EXTREME_BIG)
	{
		for (y=0; y<26; y++)
		{
			w=font16x26[ascii][a];
			for (x=0; x<8; x++)
			{
				if (w&1) LCD_SetPoint( Xpos + x, Ypos + y, charColor );
				else if(bkColor != COLOR_NONE) LCD_SetPoint( Xpos + x, Ypos + y, bkColor );
				w=w>>1;
			}

			w=font16x26[ascii][a+1];
			for (x=8; x<16; x++)
			{
				if (w&1) LCD_SetPoint( Xpos + x, Ypos + y, charColor );
				else if(bkColor != COLOR_NONE) LCD_SetPoint( Xpos + x, Ypos + y, bkColor );
				w=w>>1;
			}
			a+=2;
		}
	}

}


/*******************************************************************************
* Function Name  : GetASCIICode
* Description    : get ASCII code data
* Input          : - ASCII: Input ASCII code
* Output         : - *pBuffer: Store data pointer
* Return         : None
* Attention	 	 : None
*******************************************************************************/
void GetASCIICode(unsigned char* pBuffer,unsigned char ASCII)
{
    memcpy(pBuffer,AsciiLib[(ASCII - 32)] ,16);
}


/*******************************************************************************
* Function Name  : GetFontHeight
* Description    : get height of font
* Input          : - font: font type
* Return         : int: font height
* Attention	 	 : None
*******************************************************************************/
int GetFontHeight(font_t font)
{
    if(font == FONT_ORIGIN) return FONT_ORIGIN_HEIGHT;
    if(font == FONT_SMALL) return FONT_SMALL_HEIGHT;
    if(font == FONT_NORMAL) return FONT_NORMAL_HEIGHT;
    if(font == FONT_BIG) return FONT_BIG_HEIGHT;
    if(font == FONT_EXTREME_BIG) return FONT_EXTREME_BIG_HEIGHT;
    return -1;
}


/*******************************************************************************
* Function Name  : GetFontWidth
* Description    : get height of font
* Input          : - font: font type
* Return         : int: font width
* Attention	 	 : None
*******************************************************************************/
int GetFontWidth(font_t font)
{
    if(font == FONT_ORIGIN) return FONT_ORIGIN_WIDTH;
    if(font == FONT_SMALL) return FONT_SMALL_WIDTH;
    if(font == FONT_NORMAL) return FONT_NORMAL_WIDTH;
    if(font == FONT_BIG) return FONT_BIG_WIDTH;
    if(font == FONT_EXTREME_BIG) return FONT_EXTREME_BIG_WIDTH;
    return -1;
}


/*******************************************************************************
* Function Name  : GetCenterTextX
* Description    :  Calculate Text X coordinate for center position
* Input          : - text: Text string
*                  - font: Font type
*                  - width: Space for text
*                  - offset: insertion text position
* Return         : - int: X coordinate
* Attention	 	 : None
*******************************************************************************/
int GetCenterTextX(const char* text, font_t font, int width, int offset)
{
	if(strlen(text) <= (width/GetFontWidth(font))-1 && width <= GLCD_WIDTH)
    {
        return (offset + (width/2 - (strlen(text) * GetFontWidth(font))/2));
    }
	return offset;
}


/*******************************************************************************
* Function Name  : GetCenterTextY
* Description    :  Calculate Text Y coordinate for center position
* Input          : - font: Font type
*                  - height: Space for text
*                  - offset: insertion text position
* Return         : - int: Y coordinate
* Attention	 	 : None
*******************************************************************************/
int GetCenterTextY(font_t font, int height, int offset)
{
	if(height <= GLCD_HEIGHT)
    {
        return (1+offset + (height/2 - (GetFontHeight(font)/2)));
    }
	return offset;
}


/******************************************************************************
* Function Name  : LCD_Text
* Description    : Displays the string
* Input          :  - Xpos: Horizontal coordinate
*                   - Ypos: Vertical coordinate
*		            - str: Displayed string
*		            - charColor: Character color
*		            - bkColor: Background color
*                   - font: text font
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_Text(unsigned short Xpos, unsigned short Ypos, const char *str, color_t Color, color_t bkColor, font_t font)
{
    unsigned short TempChar;
    do
    {
			TempChar = *str++;
			if(TempChar!=195 && TempChar!=194)
			{
				PutChar( Xpos, Ypos, TempChar, Color, bkColor, font );
				if( Xpos < vinfo.xres - 8 )
				{
					if(font == FONT_ORIGIN) Xpos += FONT_ORIGIN_WIDTH;
					if(font == FONT_SMALL) Xpos += FONT_SMALL_WIDTH;
					if(font == FONT_NORMAL) Xpos += FONT_NORMAL_WIDTH;
					if(font == FONT_BIG) Xpos += FONT_BIG_WIDTH;
					if(font == FONT_EXTREME_BIG) Xpos += FONT_EXTREME_BIG_WIDTH;
				}
				else if ( Ypos < vinfo.yres - 16 )
				{
					Xpos = 0;
					if(font == FONT_ORIGIN) Ypos += FONT_ORIGIN_HEIGHT + 2;
					if(font == FONT_SMALL) Ypos += FONT_SMALL_HEIGHT + 2;
					if(font == FONT_NORMAL) Ypos += FONT_NORMAL_HEIGHT + 2;
					if(font == FONT_BIG) Ypos += FONT_BIG_HEIGHT + 2;
					if(font == FONT_EXTREME_BIG) Ypos += FONT_EXTREME_BIG_WIDTH + 2;
				}
				else
				{
					Xpos = 0;
					Ypos = 0;
				}
			}
    }
    while ( *str != 0 );
}


/******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Bresenham's line algorithm
* Input          : - x1: A point line coordinates
*                  - y1: A point column coordinates
*                  - x2: B point line coordinates
*                  - y2: B point column coordinates
*                  - col: Line color
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void LCD_DrawLine(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2, color_t col)
{
    unsigned short n, deltax, deltay, sgndeltax, sgndeltay, deltaxabs, deltayabs, x, y, drawx, drawy;

    deltax = x2 - x1;
    deltay = y2 - y1;
    deltaxabs = abs(deltax);
    deltayabs = abs(deltay);
    sgndeltax = sgn(deltax);
    sgndeltay = sgn(deltay);
    x = deltayabs >> 1;
    y = deltaxabs >> 1;
    drawx = x1;
    drawy = y1;

    LCD_SetPoint(drawx, drawy, col);

    if (deltaxabs >= deltayabs){
        for (n = 0; n < deltaxabs; n++){
            y += deltayabs;
            if (y >= deltaxabs){
                y -= deltaxabs;
                drawy += sgndeltay;
            }
            drawx += sgndeltax;
            LCD_SetPoint(drawx, drawy, col);
        }
    } else {
        for (n = 0; n < deltayabs; n++){
            x += deltaxabs;
            if (x >= deltayabs){
                 x -= deltayabs;
                 drawx += sgndeltax;
            }
            drawy += sgndeltay;
            LCD_SetPoint(drawx, drawy, col);
        }
    }
}


/******************************************************************************
* Function Name  : sgn
* Description    : return the sign of number
* Input          : - nu: the number
* Output         : None
* Return         : 1 if > 0; -1 if < 0; 0 of = 0
* Attention      : None
*******************************************************************************/
int sgn(int nu)
{
    if (nu > 0) return 1;
    if (nu < 0) return -1;
    if (nu == 0) return 0;

    return 0;
}


/******************************************************************************
* Function Name  : LCD_DrawBox
* Description    : Multiple line  makes box
* Input          : - x1: A point line coordinates upper left corner
*                  - y1: A point column coordinates
*                  - x2: B point line coordinates lower right corner
*                  - y2: B point column coordinates
*                  - bordercol: border line color
*                  - borderwidth: Width of border
*                  - bcol: Background color
* Output         : None
* Return         : None
******************************************************************************/
void LCD_DrawBox(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, color_t backgroundcol, border_t border, unsigned short borderwidth, color_t bordercol)
{
    unsigned short i, xx0, xx1, yy0;

    if  (backgroundcol != COLOR_NONE)
    {
        for (i=0; i<y1-y0-1; i++)
        {
            xx0=x0+1;
            yy0=y0+1+i;
            xx1=x1-1;

            LCD_DrawLine(xx0, yy0, xx1, yy0, backgroundcol);
        }
    }

    if(border != BORDER_NONE)
    { // for(i=0; i<=borderwidth-1; i++)
        for(i=0; i<borderwidth; i++)
        {
            LCD_DrawLine(x1-i, y0+i, x1-i, y1-i, bordercol); // right border
            LCD_DrawLine(x0+i, y0+i, x0+i, y1-i, bordercol); // left border
            LCD_DrawLine(x0+i, y1-i, x1-i, y1-i, bordercol); // bottom border
            LCD_DrawLine(x0+i, y0+i, x1-i, y0+i, bordercol); // top border
        }
    }

    if(border == BORDER_RECT_ROUNDED) {
        LCD_SetPoint(x0, y0, COLOR_WHITE); // left top
        LCD_SetPoint(x1, y0, COLOR_WHITE); // right top
        LCD_SetPoint(x0, y1, COLOR_WHITE); // left bottom
        LCD_SetPoint(x1, y1, COLOR_WHITE); // right bottom
    }
}


/******************************************************************************
* Function Name  : drawCirclePart
* Description    : Sub for LCD_DrawCircle
* Input          : - xc:
*                  - yc:
*                  - x:
*                  - y:
*                  - col: Line color
* Output         : None
* Return         : None
******************************************************************************/
void drawCirclePart(unsigned short xc, unsigned short yc, unsigned short x, unsigned short y, color_t col)
{
    LCD_SetPoint(xc+x, yc+y, col);
    LCD_SetPoint(xc-x, yc+y, col);
    LCD_SetPoint(xc+x, yc-y, col);
    LCD_SetPoint(xc-x, yc-y, col);
    LCD_SetPoint(xc+y, yc+x, col);
    LCD_SetPoint(xc-y, yc+x, col);
    LCD_SetPoint(xc+y, yc-x, col);
    LCD_SetPoint(xc-y, yc-x, col);
}


/******************************************************************************
* Function Name  : drawCircle
* Description    : Draw a circle
* Input          : - xc: A point line coordinates center
*                  - yc: A point column coordinates center
*                  - r: radius of circle
*                  - col: Line color
* Output         : None
* Return         : None
******************************************************************************/
void drawCircle(unsigned short xc, unsigned short yc, unsigned short r, color_t col)
{
    int x = 0, y = r;
    int p = 1 - r;

    while (x < y)
    {
        drawCirclePart(xc, yc, x, y, col);
        x++;
        drawCirclePart(xc, yc, x, y, col); // RAUSNEHMEN !!!!!!!!

        if (p < 0)
            p = p + 2 * x + 1;
        else
        {
            y--;
            p = p + 2 * (x-y) + 1;
        }
        drawCirclePart(xc, yc, x, y, col);
    }
}


/******************************************************************************
* Function Name  : drawCircle
* Description    : Draw a circle with variable borderwidth
* Input          : - xc: A point line coordinates center
*                  - yc: A point column coordinates center
*                  - r: radius of circle
*                  - backgroundcol: backgroundcolor
*                  - borderwidth: width of border
*                  - bordercol: bordercolor
*                  - col: line color
* Output         : None
* Return         : None
******************************************************************************/
void LCD_DrawCircle(unsigned short xc, unsigned short yc, unsigned short r, color_t backgroundcol, unsigned short borderwidth, color_t bordercol)
{
    unsigned short i;

    if(backgroundcol != COLOR_NONE) LCD_DrawCircleFill(xc, yc, r-borderwidth+1, backgroundcol, backgroundcol);

    for(i=0; i<borderwidth; i++)
    {
        drawCircle(xc, yc, r-i, bordercol);
    }
}


/******************************************************************************
* Function Name  : LCD_DrawCircleFill
* Description    : Draw a circle filled
* Input          : - xc: A point line coordinates center
*                  - yc: A point column coordinates center
*                  - r: radius of circle
*                  - bcol: border color
*                  - col: fill color
* Output         : None
* Return         : None
******************************************************************************/
void LCD_DrawCircleFill(unsigned short x, unsigned short y, unsigned short r, color_t bcol, color_t col)
{
    int xc, yc;
    double testRadius;
    double rsqMin = (double)(r-1)*(r-1);
    double rsqMax = (double)r*r;

    int fillFlag = 1;

    /* Ensure radius is positive */
    if (r < 0) {
        r = -r;
    }

    for (yc = -r; yc < r; yc++) {
        for (xc = -r; xc < r; xc++) {
            testRadius = (double)(xc*xc + yc*yc);
            if (((rsqMin < testRadius)&&(testRadius <= rsqMax))
                || ((fillFlag)&&(testRadius <= rsqMax))) {
                LCD_SetPoint(x + xc, y + yc, col);
            }
        }
    }
    if (col != bcol) drawCircle(x, y, r, bcol);
}


/*******************************************************************************
* Function Name  : LCD_PutImage
* Description    : Show BMP
* Input          : - x: upper left corner image start
*                  - y: upper left corner image start
*                  - maxwidth: max image width
*                  - maxheight: max image height
*                  file filename full qualified path
* Output         : None
* Return         : None
* Attention      : The image must be 8 or 24 bits RGB (sub will convert to 16 bits)
*******************************************************************************/
int LCD_PutImage(unsigned short x, unsigned short y, short maxwidth, short maxheight, const char* file)
{
    UCHAR red, green, blue;
    UINT width, height;
    UINT r, c;
    BMP* bmp;

    /* Read an image file */
    bmp = BMP_ReadFile(file);
    if (BMP_GetError() != BMP_OK)
    {
       /* Print error info */
       printf( "An error has occurred: %s (code %d)\n", BMP_GetErrorDescription(), BMP_GetError() );
    }

    /* Get image's dimensions */
    width = BMP_GetWidth(bmp);
    height = BMP_GetHeight(bmp);

    if(maxwidth != -1 && width > maxwidth) width = maxwidth;
    if(maxheight != -1 && height > maxheight) height = maxheight;

    /* Iterate through all the image's pixels */
    for (c=0; c<height; ++c)
    {
        for (r=0; r<width; ++r)
        {
            BMP_GetPixelRGB(bmp, r, c, &red, &green, &blue);
            LCD_SetPoint(x+r, y+c, RGB565CONVERT(red, green, blue));
        }
    }

    return 0;
}

/*******************************************************************************************
      END FILE
********************************************************************************************/
