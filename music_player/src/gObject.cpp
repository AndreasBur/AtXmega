#include "gObject.h"

gObject::gObject()
{
    // default
    pParent = NULL;
    PosX = -1;
    PosY = -1;
    Width = -1;
    Height = -1;
    Border = BORDER_NONE;
    BorderWidth = 0;
    BorderColor = COLOR_NONE;
    BorderSelected = BORDER_NONE;
    BorderWidthSelected = 0;
    BorderColorSelected = COLOR_NONE;
    BorderChosen = BORDER_NONE;
    BorderWidthChosen = 0;
    BorderColorChosen = COLOR_NONE;
    IsSelected = false;
    IsChosen = false;
    EventFunction = NULL;
}

gObject::gObject(border_t sBorder, int sBorderWidth, color_t sBorderColor, border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected)
{
    Border = sBorder;
    BorderColor = sBorderColor;
    BorderWidth = sBorderWidth;
    BorderSelected = sBorderSelected;
    BorderColorSelected = sBorderColorSelected;
    BorderWidthSelected = sBorderWidthSelected;
    // default
    pParent = NULL;
    BorderChosen = sBorderSelected;
    BorderColorChosen = sBorderColorSelected;
    BorderWidthChosen = sBorderWidthSelected;
    PosX = -1;
    PosY = -1;
    Width = -1;
    Height = -1;
    IsSelected = false;
    IsChosen = false;
    EventFunction = NULL;
}

gObject::~gObject()
{

}

int gObject::getPosXabs() const
{
    int PosXabs = PosX;
    gObject* pParentTmp = pParent;

    while(pParentTmp != NULL)
    {
        PosXabs += pParentTmp->getPosX();
        pParentTmp = pParentTmp->getParent();
    }
    return PosXabs;
}

int gObject::getPosYabs() const
{
    int PosYabs = PosY;
    gObject* pParentTmp = pParent;

    while(pParentTmp)
    {
        PosYabs += pParentTmp->getPosY();
        pParentTmp = pParentTmp->getParent();
    }
    return PosYabs;
}

void gObject::setBorder(border_t sBorder, int sBorderWidth, color_t sBorderColor)
{
    Border = sBorder;
    BorderWidth = sBorderWidth;
    BorderColor = sBorderColor;
}

void gObject::setBorderSelected(border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected)
{
    BorderSelected = sBorderSelected;
    BorderWidthSelected = sBorderWidthSelected;
    BorderColorSelected = sBorderColorSelected;
}


void gObject::setBorderChosen(border_t sBorderChosen, int sBorderWidthChosen, color_t sBorderColorChosen)
{
    BorderChosen = sBorderChosen;
    BorderWidthChosen = sBorderWidthChosen;
    BorderColorChosen = sBorderColorChosen;
}

void gObject::setStyle(border_t sBorder, int sBorderWidth, color_t sBorderColor)
{
    Border = sBorder;
    BorderWidth = sBorderWidth;
    BorderColor = sBorderColor;

}

void gObject::setStyleSelected(border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected)
{
    BorderSelected = sBorderSelected;
    BorderWidthSelected = sBorderWidthSelected;
    BorderColorSelected = sBorderColorSelected;
}

void gObject::setStyleChosen(border_t sBorderChosen, int sBorderWidthChosen, color_t sBorderColorChosen)
{
    BorderChosen = sBorderChosen;
    BorderWidthChosen = sBorderWidthChosen;
    BorderColorChosen = sBorderColorChosen;
}

void gObject::drawBorder()
{
    if(PosX == -1 || PosY == -1 || Width == -1 || Height == -1) return;
    if(IsChosen) {
        if(BorderChosen == BORDER_RECT || BorderChosen == BORDER_RECT_ROUNDED)
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+Width-1, getPosYabs()+Height-1, COLOR_NONE, BorderChosen, BorderWidthChosen, BorderColorChosen);
        if(BorderChosen == BORDER_CIRCLE)
            LCD_DrawCircle(getPosXabs()+(Width/2)-1, getPosYabs()+(Height/2)-1, Width/2, COLOR_NONE, BorderWidthChosen, BorderColorChosen);
        return;
    }
    if(IsSelected) {
        if(BorderSelected == BORDER_RECT || BorderSelected == BORDER_RECT_ROUNDED)
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+Width-1, getPosYabs()+Height-1, COLOR_NONE, BorderSelected, BorderWidthSelected, BorderColorSelected);
        if(BorderSelected == BORDER_CIRCLE)
            LCD_DrawCircle(getPosXabs()+(Width/2)-1, getPosYabs()+(Height/2)-1, Width/2, COLOR_NONE, BorderWidthSelected, BorderColorSelected);
        return;
    }
    if(Border == BORDER_RECT || Border == BORDER_RECT_ROUNDED)
        LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+Width-1, getPosYabs()+Height-1, COLOR_NONE, Border, BorderWidth, BorderColor);
    if(Border == BORDER_CIRCLE)
        LCD_DrawCircle(getPosXabs()+(Width/2)-1, getPosYabs()+(Height/2)-1, Width/2, COLOR_NONE, BorderWidth, BorderColor);
}
