#include "gItem.h"

gItem::gItem()
{
    BackgroundColor = COLOR_NONE;
    pImageItem = NULL;
    pTextItem = NULL;
    ImageMarginLeft = 0;
    ImageMarginRight = 0;
    Timeout = false;
    pImageItem = NULL;
    pTextItem = NULL;
}

gItem::gItem(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    gObject::setWidth(sWidth);
    setHeight(sHeight);
    // default
    BackgroundColor = COLOR_NONE;
    ImageMarginRight = 0;
    ImageMarginLeft = 0;
    pImageItem = NULL;
    pTextItem = NULL;
}

gItem::gItem(const gItem& rhs)
{
    setParent(rhs.getParent());
    setPosX(rhs.getPosX());
    setPosY(rhs.getPosY());
    gObject::setWidth(rhs.getWidth());
    setHeight(rhs.getHeight());
    setIsSelected(rhs.getIsSelected());
    setIsChosen(rhs.getIsChosen());
    setBorder(rhs.getBorder());
    setBorderColor(rhs.getBorderColor());
    setBorderWidth(rhs.getBorderWidth());
    setBorderSelected(rhs.getBorderSelected());
    setBorderColorSelected(rhs.getBorderColorSelected());
    setBorderWidthSelected(rhs.getBorderWidthSelected());
    setBorderChosen(rhs.getBorderChosen());
    setBorderColorChosen(rhs.getBorderColorChosen());
    setBorderWidthChosen(rhs.getBorderWidthChosen());
    setEventFunction(rhs.getEventFunction());

    BackgroundColor = rhs.getBackgroundColor();

    if(rhs.pImageItem != NULL) {
        pImageItem = new gImageItem;
        *pImageItem = rhs.getImageItem();
        pImageItem->setParent(this);
    } else pImageItem = NULL;

    if(rhs.pTextItem != NULL) {
        pTextItem = new gTextItem;
        *pTextItem = rhs.getTextItem();
        pTextItem->setParent(this);
    } else pTextItem = NULL;

    ImageMarginLeft = rhs.getImageMarginLeft();
    ImageMarginRight = rhs.getImageMarginRight();
    Timeout = rhs.getTimeout();
}

gItem& gItem::operator=(const gItem& rhs)
{
    if(this == &rhs) return *this;

    setParent(rhs.getParent());
    setPosX(rhs.getPosX());
    setPosY(rhs.getPosY());
    gObject::setWidth(rhs.getWidth());
    setHeight(rhs.getHeight());
    setIsSelected(rhs.getIsSelected());
    setIsChosen(rhs.getIsChosen());
    setBorder(rhs.getBorder());
    setBorderColor(rhs.getBorderColor());
    setBorderWidth(rhs.getBorderWidth());
    setBorderSelected(rhs.getBorderSelected());
    setBorderColorSelected(rhs.getBorderColorSelected());
    setBorderWidthSelected(rhs.getBorderWidthSelected());
    setBorderChosen(rhs.getBorderChosen());
    setBorderColorChosen(rhs.getBorderColorChosen());
    setBorderWidthChosen(rhs.getBorderWidthChosen());
    setEventFunction(rhs.getEventFunction());

    BackgroundColor = rhs.getBackgroundColor();

    if(rhs.pImageItem != NULL) {
        *pImageItem = rhs.getImageItem();
    } else pImageItem = NULL;

    if(rhs.pTextItem != NULL) {
        *pTextItem = rhs.getTextItem();
    } else pTextItem = NULL;

    ImageMarginLeft = rhs.getImageMarginLeft();
    ImageMarginRight = rhs.getImageMarginRight();
    Timeout = rhs.getTimeout();

    return *this;
}

gItem::~gItem()
{
    if(pImageItem != NULL) delete pImageItem;
    if(pTextItem != NULL) delete pTextItem;
}

void gItem::setWidth(int sWidth)
{
    gObject::setWidth(sWidth);
    if(pTextItem != NULL) {
        if(pImageItem != NULL) { pTextItem->setWidth(sWidth-(ImageMarginLeft+pImageItem->getWidth()+ImageMarginRight)); }
        else { pTextItem->setWidth(sWidth); }
    }
}

void gItem::setIsSelected(bool sIsSelected)
{
    if(sIsSelected) setIsSelected();
    else clearIsSelected();
}

void gItem::setIsSelected()
{
    gObject::setIsSelected();
    if(pTextItem != NULL) {
        pTextItem->setIsSelected();
    }
}

void gItem::clearIsSelected()
{
    gObject::clearIsSelected();
    if(pTextItem != NULL) {
        pTextItem->clearIsSelected();
    }
}

void gItem::setImage(image_t Image, int Width, int Height, int MarginRight, int MarginLeft)
{
    ImageMarginRight = MarginRight;
    ImageMarginLeft = MarginLeft;

    int ImagePosY;

    if(Height < getHeight()) {
        ImagePosY = (getHeight()/2) - (Height/2);
    } else {
        ImagePosY = 0;
    }

    if(pImageItem != NULL) delete pImageItem;
    pImageItem = new gImageItem(this, MarginLeft, ImagePosY, Width, Height, Image);

    if(pTextItem != NULL) {
        pTextItem->setPosX(MarginLeft+Width+MarginRight);
        pTextItem->setWidth(getWidth()-(MarginLeft+Width+MarginRight));
        Timeout = pTextItem->getTimeout();
    }
}

void gItem::setText(std::string Text, font_t Font, color_t TextColor)
{
    if(pTextItem != NULL) delete pTextItem;

    if(pImageItem != NULL) {
        int TextPosX = ImageMarginLeft+ImageMarginRight+pImageItem->getWidth();
        int TextWidth = getWidth()-(ImageMarginLeft+ImageMarginRight+pImageItem->getWidth());
        pTextItem = new gTextItem(this, TextPosX, 0, TextWidth, getHeight());
    } else {
        pTextItem = new gTextItem(this, 0, 0, getWidth(), getHeight());
    }
    pTextItem->setStyle(COLOR_NONE, Text, Font, TextColor, BORDER_NONE, 0, COLOR_NONE);
    Timeout = pTextItem->getTimeout();
}

void gItem::timeout()
{
    if(pTextItem != NULL) {
        pTextItem->timeout();
    }
}

void gItem::draw()
{
    if(BackgroundColor != COLOR_NONE)
        LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, BackgroundColor, BORDER_NONE, 0, COLOR_NONE);
    if(pImageItem != NULL) pImageItem->draw();
    if(pTextItem != NULL) pTextItem->draw();
    drawBorder();
}

void gItem::event(event_t Event)
{
    // check if event function exists
    if(getEventFunction() != NULL) {
        getEventFunction()(Event);
        return;
    }
}
