#ifndef GANYMENUE_H
#define GANYMENUE_H

#include "gObject.h"

class gAnyMenue : public gObject
{
    public:
        gAnyMenue();
        gAnyMenue(color_t BackgroundColor, border_t sBorder, int sBorderWidth, color_t sBorderColor, border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected);
        virtual ~gAnyMenue();

        // gAnyMenue methods get functions
        //font_t getFont() const { return Font; }
        // gAnyMenue methods set functions
        //void setFont(font_t sFont) { Font = sFont; }

    protected:

    private:
        //font_t Font;
};

#endif // GANYMENUE_H
