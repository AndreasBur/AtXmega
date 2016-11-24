#ifndef MENUE_ITEM_H
#define MENUE_ITEM_H

#include <string>
#include "lcd.h"

typedef enum {
	IMAGE_NONE,
	IMAGE_SETTINGS,
	IMAGE_PLAYMUSIC
} image_t;


class menue_item
{
    public:
        menue_item();
        menue_item(std::string sText, color_t sColor=COLOR_BLACK);
        menue_item(std::string sText, image_t sImage, int sImageWidth, int sImageHeight, color_t sColor=COLOR_BLACK);
        ~menue_item();
        menue_item(const menue_item &);

        std::string getText() const { return Text; }
        image_t getImage() const { return Image; }
        color_t getColor() const { return Color; }
        void setText(std::string sText);
        void setImage(image_t sImage, int sImageWidth, int sImageHeight);
        void setColor(color_t sColor);
    protected:
    private:
        std::string Text;
        image_t Image;
        int ImageWidth;
        int ImageHeight;
        color_t Color;
};

#endif // MENUE_ITEM_H
