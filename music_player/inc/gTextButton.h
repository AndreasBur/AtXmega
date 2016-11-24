#ifndef GTEXTBUTTON_H
#define GTEXTBUTTON_H

#include <string>
#include "gAnyButton.h"

class gTextButton : public gAnyButton
{
    public:
        gTextButton(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight);
        virtual ~gTextButton();

        // gTextButton methods get functions
        std::string getText() const { return Text; }
        std::string getTextPushed() const { return TextPushed; }
        align_t getTextAlign() const { return TextAlign; }
        align_t getTextAlignPushed() const { return TextAlignPushed; }
        font_t getFont() const { return Font; }
        font_t getFontPushed() const { return FontPushed; }
        color_t getTextColor() const { return TextColor; }
        color_t getTextColorPushed() const { return TextColorPushed; }
        // gTextButton methods set functions
        void setText(std::string sText) { Text = sText; }
        void setTextPushed(std::string sTextPushed) { Text = sTextPushed; }
        void setTextAlign(align_t sTextAlign) { TextAlign = sTextAlign; }
        void setTextAlignPushed(align_t sTextAlignPushed) { TextAlignPushed = sTextAlignPushed; }
        void setFont(font_t sFont) { Font = sFont; }
        void setFontPushed(font_t sFontPushed) { FontPushed = sFontPushed; }
        void setTextColor(color_t sTextColor) { TextColor = sTextColor; }
        void setTextColorPushed(color_t sTextColorPushed) { TextColorPushed = sTextColorPushed; }

        // gTextButton methods control functions
        virtual void setStyle(color_t sBackgroundColor, std::string sText, font_t sFont, border_t sBorder, int sBorderWidth, color_t sBorderColor);
        virtual void setStylePushed(color_t sBackgroundColorPushed, std::string sText, font_t sFontPushed, border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed);
        virtual void draw();
        virtual void drawBorder();

    protected:

    private:
        std::string Text;
        std::string TextPushed;
        align_t TextAlign;
        align_t TextAlignPushed;
        font_t Font;
        font_t FontPushed;
        color_t TextColor;
        color_t TextColorPushed;

};

#endif // GTEXTBUTTON_H
