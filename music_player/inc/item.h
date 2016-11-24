#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "lcd.h"
#include "images.h"


class item
{
    public:
        item();
        item(std::string sText, color_t sColor=COLOR_BLACK);
        item(std::string sText, image_t sImage, int sImageWidth, int sImageHeight, color_t sColor=COLOR_BLACK);
        ~item();
        //item(const item &);

        std::string getText() const { return Text; }
        image_t getImage() const { return Image; }
        color_t getColor() const { return Color; }
        void setText(std::string sText);
        void setImage(image_t sImage, int sImageWidth, int sImageHeight);
        void setColor(color_t sColor);

        bool hasImage() const;
    protected:
    private:
        std::string Text;
        image_t Image;
        int ImageWidth;
        int ImageHeight;
        color_t Color;
};

#endif // ITEM_H
