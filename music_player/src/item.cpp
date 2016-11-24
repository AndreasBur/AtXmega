#include "item.h"

item::item()
{

}

item::item(std::string sText, color_t sColor)
{
    Text = sText;
    Color = sColor;
    Image = IMAGE_NONE;
}

item::item(std::string sText, image_t sImage, int sImageWidth, int sImageHeight, color_t sColor)
{
    Text = sText;
    Image = sImage;
    ImageWidth = sImageWidth;
    ImageHeight = sImageHeight;
    Color = sColor;
}

item::~item()
{

}
/*
item::item(const item & rhs)
{
    Text = rhs.getText();
    Color = rhs.getColor();
    Image = rhs.getImage();
}
*/
void item::setText(std::string sText)
{
    Text = sText;
}

void item::setImage(image_t sImage, int sImageWidth, int sImageHeight)
{
    Image = sImage;
    ImageWidth = sImageWidth;
    ImageHeight = sImageHeight;
}

void item::setColor(color_t sColor)
{
    Color = sColor;
}

bool item::hasImage() const {
    if(Image == IMAGE_NONE) return false;
    else return true;
}


