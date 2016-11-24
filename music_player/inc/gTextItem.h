#ifndef GTEXTITEM_H
#define GTEXTITEM_H

#include <string>
#include <algorithm>
#include "lcd.h"
#include "event.h"
#include "gObject.h"

class gTextItem : public gObject
{
    public:
        gTextItem();
        gTextItem(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight);
        virtual ~gTextItem();

        // gTextItem methods get functions
        color_t getBackgroundColor() const { return BackgroundColor; }
        std::string getText() const { return Text; }
        align_t getTextAlign() const { return TextAlign; }
        font_t getFont() const { return Font; }
        color_t getTextColor() const { return TextColor; }
        bool getTimeout() const { return Timeout; }
        // gTextItem methods set functions
        void setWidth(int sWidth);
        void setBackgroundColor(color_t sBackgroundColor) { BackgroundColor = sBackgroundColor; }
        void setText(std::string sText);
        void setTextAlign(align_t sTextAlign) { TextAlign = sTextAlign; }
        void setFont(font_t sFont) { Font = sFont; }
        void setTextColor(color_t sTextColor) { TextColor = sTextColor; }
        void setTimeout(bool sTimeout) { Timeout = sTimeout; }
        virtual void setIsSelected(bool sIsSelected);
        virtual void setIsSelected();

        // gTextItem methods
        void appendText(std::string sText) { Text.append(sText); };
        void timeout();
        virtual void setStyle(color_t sBackgroundColor, std::string sText, font_t sFont, color_t sTextColor ,border_t sBorder=BORDER_NONE, int sBorderWidth=0, color_t sBorderColor=COLOR_NONE);
        virtual void draw();
        virtual void event(event_t Event);

    protected:

    private:
        void calcMaxTextLength();
        color_t BackgroundColor;
        std::string Text;
        static std::string TextRot;
        align_t TextAlign;
        font_t Font;
        int MaxTextLength;
        color_t TextColor;
        bool Timeout;
};


#endif // GTEXTITEM_H
