#include "gImageButton.h"

gImageButton::gImageButton(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, image_t sImage, image_t sImagePushed)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    Image = sImage;
    ImagePushed = sImagePushed;
    ImageSelected = sImage;
    ImagePushedSelected = sImagePushed;
    ImageChosen = sImage;
    ImagePushedChosen = sImagePushed;
}

gImageButton::~gImageButton()
{

}

void gImageButton::setImages(image_t sImage, image_t sImageSelected, image_t sImageChosen)
{
    Image = sImage;
    ImageSelected = sImageSelected;
    ImageChosen = sImageChosen;
}

void gImageButton::setImagesPushed(image_t sImagePushed, image_t sImagePushedSelected, image_t sImagePushedChosen)
{
    ImagePushed = sImagePushed;
    ImagePushedSelected = sImagePushedSelected;
    ImagePushedChosen = sImagePushedChosen;
}

void gImageButton::draw()
{
    if(getIsPushed()) {
        if(getIsChosen()) {
            if(ImagePushedChosen == IMAGE_NONE) return;
            LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImagePushedChosen));
        }
        if(getIsSelected()) {
            if(ImagePushedSelected == IMAGE_NONE) return;
            LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImagePushedSelected));
        }
        if(ImagePushed == IMAGE_NONE) return;
            LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImagePushed));
    } else {
        if(getIsChosen()) {
            if(ImageChosen == IMAGE_NONE) return;
            LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImageChosen));
        }
        if(getIsSelected()) {
            if(ImageSelected == IMAGE_NONE) return;
            LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(ImageSelected));
        }
        if(Image == IMAGE_NONE) return;
            LCD_PutImage(getPosXabs(), getPosYabs(), getWidth(), getHeight(), getImagePath(Image));
    }
    drawBorder();
}

void gImageButton::drawBorder()
{
    bool BorderRect;

    if(getIsChosen()) {
        BorderRect = getBorderChosen() == BORDER_RECT || getBorderChosen() == BORDER_RECT_ROUNDED;
        if((getIsPushed() && BorderRect) || (getIsPushed() == false && BorderRect))
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, COLOR_NONE, getBorderChosen(), getBorderWidthChosen(), getBorderColorChosen());
        if((getIsPushed() && getBorderChosen() == BORDER_CIRCLE) || (getIsPushed() == false && getBorderChosen() == BORDER_CIRCLE))
            LCD_DrawCircle((getPosXabs()+(getWidth()/2))-1, (getPosYabs()+(getHeight()/2))-1, getWidth()/2, COLOR_NONE, getBorderWidthChosen(), getBorderColorChosen());
        return;
    }
    if(getIsSelected()) {
        BorderRect = getBorderSelected() == BORDER_RECT || getBorderSelected() == BORDER_RECT_ROUNDED;
        if((getIsPushed() && BorderRect) || (getIsPushed() == false && BorderRect))
            LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, COLOR_NONE, getBorderSelected(), getBorderWidthSelected(), getBorderColorSelected());
        if((getIsPushed() && getBorderSelected() == BORDER_CIRCLE) || (getIsPushed() == false && getBorderSelected() == BORDER_CIRCLE))
            LCD_DrawCircle((getPosXabs()+(getWidth()/2))-1, (getPosYabs()+(getHeight()/2))-1, getWidth()/2, COLOR_NONE, getBorderWidthSelected(), getBorderColorSelected());
        return;
    }
    BorderRect = getBorder() == BORDER_RECT || getBorder() == BORDER_RECT_ROUNDED;
    if((getIsPushed() && BorderRect) || (getIsPushed() == false && BorderRect))
        LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, COLOR_NONE, getBorder(), getBorderWidth(), getBorderColor());
    if((getIsPushed() && getBorder() == BORDER_CIRCLE) || (getIsPushed() == false && getBorder() == BORDER_CIRCLE))
        LCD_DrawCircle((getPosXabs()+(getWidth()/2))-1, (getPosYabs()+(getHeight()/2))-1, getWidth()/2, COLOR_NONE, getBorderWidth(), getBorderColor());
}
