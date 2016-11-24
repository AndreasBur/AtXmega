#include "menue_item.h"

menue_item::menue_item()
{

}

menue_item::menue_item(std::string sText, color_t sColor)
{
    Text = sText;
    Color = sColor;
    Image = IMAGE_NONE;
}

menue_item::menue_item(std::string sText, image_t sImage, int sImageWidth, int sImageHeight, color_t sColor)
{
    Text = sText;
    Image = sImage;
    ImageWidth = sImageWidth;
    ImageHeight = sImageHeight;
    Color = sColor;
}

menue_item::~menue_item()
{

}

menue_item::menue_item(const menue_item & rhs)
{
    Text = rhs.getText();
    Color = rhs.getColor();
    Image = rhs.getImage();
}

void menue_item::setText(std::string sText)
{
    Text = sText;
}

void menue_item::setImage(image_t sImage, int sImageWidth, int sImageHeight)
{
    Image = sImage;
    ImageWidth = sImageWidth;
    ImageHeight = sImageHeight;
}

void menue_item::setColor(color_t sColor)
{
    Color = sColor;
}


