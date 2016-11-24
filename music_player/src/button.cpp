#include "button.h"

button::button()
{

}

button::button(int sPosX, int sPosY, int sWidth, int sHeight, bF_void sCbFunction)
{
    PosX = sPosX;
    PosY = sPosY;
    Width = sWidth;
    Height = sHeight;
    CbFunction = sCbFunction;
    // default
    BackgroundColor = COLOR_WHITE;
    BackgroundColorPushed = COLOR_WHITE;
    Font = FONT_NORMAL;
    FontPushed = FONT_NORMAL;
    TextColor = COLOR_BLACK;
    TextColorPushed = COLOR_BLACK;
    Border = BORDER_NONE;
    BorderPushed = BORDER_NONE;
    BorderWidth = 0;
    BorderWidthPushed = 0;
    BorderColor = COLOR_NONE;
    BorderColorPushed = COLOR_NONE;
    BorderPushed = BORDER_NONE;
    Image = IMAGE_NONE;
    ImagePushed = IMAGE_NONE;
    Pushed = false;
}

button::button(int sPosX, int sPosY, image_t sImage, image_t sImagePushed, bF_void sCbFunction)
{
    PosX = sPosX;
    PosY = sPosY;
    Image = sImage;
    ImagePushed = sImagePushed;
    CbFunction = sCbFunction;
    // default
    BackgroundColor = COLOR_WHITE;
    BackgroundColorPushed = COLOR_WHITE;
    Font = FONT_NONE;
    FontPushed = FONT_NONE;
    TextColor = COLOR_NONE;
    TextColorPushed = COLOR_NONE;
    Border = BORDER_NONE;
    BorderPushed = BORDER_NONE;
    BorderWidth = 0;
    BorderWidthPushed = 0;
    BorderColor = COLOR_NONE;
    BorderColorPushed = COLOR_NONE;
    Pushed = false;
}

button::~button()
{

}

void button::push()
{
    Pushed = true;
    if(CbFunction != NULL) CbFunction();
}

void button::toggle()
{
    Pushed = !Pushed;
    if(Pushed) {
        if(CbFunction != NULL) CbFunction();
    }
}

void button::setStyle(color_t sBackgroundColor, font_t sFont, border_t sBorder, int sBorderWidth, color_t sBorderColor)
{
    BackgroundColor = sBackgroundColor;
    Font = sFont;
    BorderWidth = sBorderWidth;
    BorderColor = sBorderColor;
}

void button::setStylePushed(color_t sBackgroundColorPushed, font_t sFontPushed, border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed)
{
    BackgroundColorPushed = sBackgroundColorPushed;
    FontPushed = sFontPushed;
    BorderWidthPushed = sBorderWidthPushed;
    BorderColorPushed = sBorderColorPushed;
}

void button::draw()
{
    std::string buffer;

    if(Image == IMAGE_NONE) {
        if(Pushed) {
            LCD_DrawBox(PosX, PosY, PosX+Width, PosY+Height, BackgroundColorPushed, BorderPushed, BorderWidthPushed, BorderColorPushed);
            if(TextPushed.empty() == false) {
                int MaxTextLengthPushed = Width / GetFontWidth(FontPushed);
                // check text length
                buffer = Text.substr(0, MaxTextLengthPushed);
                LCD_Text(GetCenterTextX(buffer.c_str(), FontPushed, Width, PosX), GetCenterTextY(FontPushed, Height, PosY), buffer.c_str(), TextColorPushed, COLOR_NONE, FontPushed);
            }
        } else {
            LCD_DrawBox(PosX, PosY, PosX+Width, PosY+Height, BackgroundColor, Border, BorderWidth, BorderColor);
            if(Text.empty() == false) {
                int MaxTextLength = Width / GetFontWidth(Font);
                // check text length
                buffer = Text.substr(0, MaxTextLength);
                LCD_Text(GetCenterTextX(buffer.c_str(), Font, Width, PosX), GetCenterTextY(Font, Height, PosY), buffer.c_str(), TextColor, COLOR_NONE, Font);
            }
        }
    } else {
        if(Pushed) {
            LCD_PutImage(PosX, PosY, "path to image");
        } else {
            LCD_PutImage(PosX, PosY, "path to imagePushed");
        }
    }
}
