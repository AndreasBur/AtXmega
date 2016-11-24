#include "gImageItem.h"

gImageItem::gImageItem()
{
    Image = IMAGE_NONE;
    ImageSelected = IMAGE_NONE;
    ImageChosen = IMAGE_NONE;
}

gImageItem::gImageItem(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, image_t sImage)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    Image = sImage;
    //default
    ImageSelected = sImage;
    ImageChosen = sImage;
}

gImageItem::~gImageItem()
{

}

void gImageItem::draw()
{
    if(getIsChosen()) {
        LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImageChosen));
        return;
    }
    if(getIsSelected()) {
        LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImageSelected));
        return;
    }
    LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(Image));
    drawBorder();
}

void gImageItem::event(event_t Event)
{
    // check if event function exists
    if(getEventFunction() != NULL) {
        getEventFunction()(Event);
        return;
    }
}
