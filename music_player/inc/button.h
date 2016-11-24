#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "lcd.h"
#include "images.h"

typedef void (*bF_void)(void);

class button
{
    public:
        button();
        button(int sPosX, int sPosY, int sWidth, int sHeight, bF_void sCbFunction=NULL);
        button(int sPosX, int sPosY, image_t sImage, image_t sImagePushed=IMAGE_NONE, bF_void sCbFunction=NULL);
        ~button();
        // get methods
        int getPosX() const { return PosX; }
        int getPoxY() const { return PosY; }
        int getWidth() const { return Width; }
        int getHeight() const { return Height; }
        color_t getBackgroundColor() const { return BackgroundColor; }
        color_t getBackgroundColorPusehd() const { return BackgroundColorPushed; }
        std::string getText() const { return Text; }
        std::string getTextPushed() const { return TextPushed; }
        font_t getFont() const { return Font; }
        font_t getFontPushed() const { return FontPushed; }
        color_t getTextColor() const { return TextColor; }
        color_t getTextColorPushed() const { return TextColorPushed; }
        border_t getBorder() const { return Border; }
        border_t getBorderPushed() const { return BorderPushed; }
        int getBorderWidth() const { return BorderWidth; }
        int getBorderWidthPushed() const { return BorderWidthPushed; }
        color_t getBorderColor() const { return BorderColor; }
        color_t getBorderColorPushed() const { return BorderColorPushed; }
        image_t getImage() const { return Image; }
        int getImageWidth() const;
        int getImageHeight() const;
        image_t getImagePushed() const { return ImagePushed; }
        int getImagePushedWidth() const;
        int getImagePushedHeight() const;
        bool getPushed() const {return Pushed; }
        bool getIsSelected() const { return IsSelected; }
        // set methods
        void setPos(int sPosX, int sPosY) { PosX = sPosX; PosY = sPosY; }
        void setPosX(int sPosX) { PosX = sPosX; }
        void setPosY(int sPosY) { PosY = sPosY; }
        void setWidth(int sWidth) { Width = sWidth; }
        void setHeight(int sHeight) { Height = sHeight; }
        void setBackgroundColor(color_t sBackgroundColor) { BackgroundColor = sBackgroundColor; }
        void setBackgroundColorPushed(color_t sBackgroundColorPushed) { BackgroundColorPushed = sBackgroundColorPushed; }
        void setText(std::string sText, font_t sFont, color_t sTextColor) { Text = sText; Font = sFont; TextColor = sTextColor; }
        void setTextPushed(std::string sTextPushed, font_t sFontPushed, color_t sTextColorPushed) { TextPushed = sTextPushed; Font = sFontPushed; TextColorPushed = sTextColorPushed; }
        void setText(std::string sText) { Text = sText; }
        void setTextPushed(std::string sTextPushed) { TextPushed = sTextPushed; }
        void setTextColor(color_t sTextColor) { TextColor = sTextColor; }
        void setTextColorPushed(color_t sTextColorPushed) { TextColorPushed = sTextColorPushed; }
        void setFont(font_t sFont) { Font = sFont; }
        void setFontPushed(font_t sFontPushed) { FontPushed = sFontPushed; }
        void setBorder(border_t sBorder, int sBorderWidth, color_t sBorderColor) { Border = sBorder; BorderWidth = sBorderWidth; BorderColor = sBorderColor; }
        void setBorderPushed(border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed) { BorderPushed = sBorderPushed; BorderWidthPushed = sBorderWidthPushed; BorderColorPushed = sBorderColorPushed; }
        void setBorder(border_t sBorder) { Border = sBorder; }
        void setBorderPushed(border_t sBorderPushed) { BorderPushed = sBorderPushed; }
        void setBorderWidth(int sBorderWidth) { BorderWidth = sBorderWidth; }
        void setBorderWidthPushed(int sBorderWidthPushed) { BorderWidthPushed = sBorderWidthPushed; }
        void setBorderColor(color_t sBorderColor) { BorderColor = sBorderColor; }
        void setBorderColorPushed(color_t sBorderColorPushed) { BorderColorPushed = sBorderColorPushed; }
        void setImage(image_t sImage) { Image = sImage; }
        void setImagePushed(image_t sImagePushed) { ImagePushed = sImagePushed; }
        void setStyle(color_t sBackgroundColor, font_t sFont, border_t sBorder, int sBorderWidth, color_t sBorderColor);
        void setStylePushed(color_t sBackgroundColorPushed, font_t sFontPushed, border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed);
        void setIsSelected(bool sIsSelected) { IsSelected = sIsSelected; }

        void push();
        void release() { Pushed = false; }
        void toggle();
        void draw();
    protected:
    private:
        int PosX;
        int PosY;
        int Width;
        int Height;
        color_t BackgroundColor;
        color_t BackgroundColorPushed;
        std::string Text;
        std::string TextPushed;
        font_t Font;
        font_t FontPushed;
        color_t TextColor;
        color_t TextColorPushed;
        border_t Border;
        border_t BorderPushed;
        int BorderWidth;
        int BorderWidthPushed;
        color_t BorderColor;
        color_t BorderColorPushed;
        image_t Image;
        image_t ImagePushed;
        bF_void CbFunction;
        bool Pushed;
        bool IsSelected;
};

#endif // BUTTON_H
