#include "gAnyMenue.h"

gAnyMenue::gAnyMenue()
{
    //Font = FONT_NONE;
}

gAnyMenue::gAnyMenue(color_t BackgroundColor, border_t sBorder, int sBorderWidth, color_t sBorderColor, border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected)
    : gObject(BORDER_RECT, 3, COLOR_BLACK, BORDER_RECT, 3, COLOR_RED)
{
    //Font = FONT_NONE;
}

gAnyMenue::~gAnyMenue()
{
    //dtor
}

