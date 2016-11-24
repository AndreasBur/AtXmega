#include "gTextButton.h"

gTextButton::gTextButton(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    Text = "";
    TextPushed = "";
    TextAlign = ALIGN_CENTER;
    TextAlignPushed = ALIGN_CENTER;
    Font = FONT_NONE;
    FontPushed = FONT_NONE;
    TextColor = COLOR_NONE;
    TextColorPushed = COLOR_NONE;
    setBackgroundColorPushed(COLOR_NONE);
}

gTextButton::~gTextButton()
{

}

void gTextButton::setStyle(color_t sBackgroundColor, std::string sText, font_t sFont, border_t sBorder, int sBorderWidth, color_t sBorderColor)
{
    setBackgroundColor(sBackgroundColor);
    Text = sText;
    Font = sFont;
    setBorder(sBorder);
    setBorderWidth(sBorderWidth);
    setBorderColor(sBorderColor);
}

void gTextButton::setStylePushed(color_t sBackgroundColorPushed, std::string sTextPushed, font_t sFontPushed, border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed)
{
    setBackgroundColorPushed(sBackgroundColorPushed);
    TextPushed = sTextPushed;
    FontPushed = sFontPushed;
    setBorderPushed(sBorderPushed);
    setBorderWidthPushed(sBorderWidthPushed);
    setBorderColorPushed(sBorderColorPushed);
}

void gTextButton::draw()
{
    if(getIsPushed()) {
        if(TextPushed.empty() == false) {
            // draw backgroundcolor
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, getBackgroundColorPushed(), BORDER_RECT_ROUNDED, 0, COLOR_NONE);
            // check text length
            int MaxTextLengthPushed = (getWidth()-2*DIST_TEXT_BORDER) / GetFontWidth(FontPushed);
            if(TextAlignPushed == ALIGN_CENTER) {
                LCD_Text(GetCenterTextX(TextPushed.substr(0, MaxTextLengthPushed).c_str(), FontPushed, getWidth(), getPosXabs()), GetCenterTextY(FontPushed, getHeight(), getPosYabs()), TextPushed.substr(0, MaxTextLengthPushed).c_str(), TextColorPushed, COLOR_NONE, FontPushed);
            }
            if(TextAlignPushed == ALIGN_LEFT) {
                LCD_Text(getPosXabs()+DIST_TEXT_BORDER, GetCenterTextY(FontPushed, getHeight(), getPosYabs()), TextPushed.substr(0, MaxTextLengthPushed).c_str(), TextColorPushed, COLOR_NONE, FontPushed);
            }
        }
    } else {
        if(Text.empty() == false) {
            // draw backgroundcolor
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, getBackgroundColor(), BORDER_RECT_ROUNDED, 0, COLOR_NONE);
            // check text length
            int MaxTextLength = (getWidth()-2*DIST_TEXT_BORDER) / GetFontWidth(Font);
            if(TextAlign == ALIGN_CENTER) {
                LCD_Text(GetCenterTextX(Text.substr(0, MaxTextLength).c_str(), Font, getWidth(), getPosXabs()), GetCenterTextY(Font, getHeight(), getPosYabs()), Text.substr(0, MaxTextLength).c_str(), TextColor, COLOR_NONE, Font);
            }
            if(TextAlign == ALIGN_LEFT) {
                LCD_Text(getPosXabs()+DIST_TEXT_BORDER, GetCenterTextY(Font, getHeight(), getPosYabs()), Text.substr(0, MaxTextLength).c_str(), TextColor, COLOR_NONE, Font);
            }
        }
    }
    drawBorder();
}

void gTextButton::drawBorder()
{
    if(getIsChosen() || getIsSelected() || getIsPushed() == false) {
        gObject::drawBorder();
        return;
    }
    if(getIsPushed()) {
        if(getBorderPushed() == BORDER_RECT || getBorderPushed() == BORDER_RECT_ROUNDED)
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, COLOR_NONE, getBorderPushed(), getBorderWidthPushed(), getBorderColorPushed());
        if(getBorderPushed() == BORDER_CIRCLE)
            LCD_DrawCircle(getPosXabs()+(getWidth()/2)-1, getPosYabs()+(getHeight()/2)-1, getWidth()/2, COLOR_NONE, getBorderWidthPushed(), getBorderColorPushed());
    }
}
