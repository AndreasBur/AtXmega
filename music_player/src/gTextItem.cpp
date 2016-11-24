#include "gTextItem.h"

std::string gTextItem::TextRot = "";

gTextItem::gTextItem()
{
    BackgroundColor = COLOR_NONE;
    Text = "";
    TextAlign = ALIGN_LEFT;
    Font = FONT_NONE;
    MaxTextLength = 0;
    TextColor = COLOR_NONE;
    Timeout = false;
}

gTextItem::gTextItem(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    // default
    BackgroundColor = COLOR_NONE;
    Text = "";
    TextAlign = ALIGN_LEFT;
    Font = FONT_NONE;
    TextColor = COLOR_NONE;
    Timeout = false;
}

gTextItem::~gTextItem()
{

}

void gTextItem::setWidth(int sWidth)
{
    gObject::setWidth(sWidth);
    calcMaxTextLength();
}

void gTextItem::setText(std::string sText)
{
    Text = sText;
    if((int)Text.size() > MaxTextLength) Timeout = true;
    else Timeout = false;
}

void gTextItem::setIsSelected(bool sIsSelected)
{
    if(sIsSelected) setIsSelected();
    else gObject::clearIsSelected();
}

void gTextItem::setIsSelected()
{
    gObject::setIsSelected();
    TextRot = Text;
    if(Timeout) TextRot.append(" - ");
}

void gTextItem::timeout()
{
    if(getIsSelected() && Timeout)
        std::rotate(TextRot.begin(), TextRot.begin()+1, TextRot.end());
}

void gTextItem::setStyle(color_t sBackgroundColor, std::string sText, font_t sFont, color_t sTextColor ,border_t sBorder, int sBorderWidth, color_t sBorderColor)
{
    setBackgroundColor(sBackgroundColor);
    Text = sText;
    Font = sFont;
    TextColor = sTextColor;
    calcMaxTextLength();
    setBorder(sBorder);
    setBorderWidth(sBorderWidth);
    setBorderColor(sBorderColor);
}

void gTextItem::draw()
{
    std::string bText;

    if(getIsSelected()) bText = TextRot;
    else bText = Text;

    // draw backgroundcolor
    LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, BackgroundColor, BORDER_RECT, 0, COLOR_NONE);

    if(TextAlign == ALIGN_CENTER) {
        LCD_Text(GetCenterTextX(bText.substr(0, MaxTextLength).c_str(), Font, getWidth(), getPosXabs()), GetCenterTextY(Font, getHeight(), getPosYabs()), bText.substr(0, MaxTextLength).c_str(), TextColor, COLOR_NONE, Font);
    }
    if(TextAlign == ALIGN_LEFT) {
        LCD_Text(getPosXabs()+DIST_TEXT_BORDER, GetCenterTextY(Font, getHeight(), getPosYabs()), bText.substr(0, MaxTextLength).c_str(), TextColor, COLOR_NONE, Font);
    }
    drawBorder();
}

void gTextItem::event(event_t Event)
{
    // check if event function exists
    if(getEventFunction() != NULL) {
        getEventFunction()(Event);
        return;
    }
}

inline void gTextItem::calcMaxTextLength()
{
    MaxTextLength = (getWidth()-2*DIST_TEXT_BORDER) / GetFontWidth(Font);
    if((int)Text.size() > MaxTextLength) Timeout = true;
    else Timeout = false;
}
