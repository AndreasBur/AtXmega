#ifndef GIMAGEBUTTON_H
#define GIMAGEBUTTON_H

#include "lcd.h"
#include "images.h"
#include "gAnyButton.h"
#include <iostream>

class gImageButton : public gAnyButton
{
    public:
        gImageButton(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, image_t sImage, image_t sImagePushed);
        virtual ~gImageButton();

        // gImageButton methods get functions
        image_t getImage() const { return Image; }
        image_t getImagePushed() const { return ImagePushed; }
        image_t getImageSelected() const { return ImageSelected; }
        image_t getImagePushedSelected() const { return ImagePushedSelected; }
        image_t getImageChosen() const { return ImageChosen; }
        image_t getImagePushedChosen() const { return ImagePushedChosen; }
        // gImageButton methods set functions
        void setImage(image_t sImage) { Image = sImage; }
        void setImagePushed(image_t sImagePushed) { ImagePushed = sImagePushed; }
        void setImageSelected(image_t sImageSelected) { ImageSelected = sImageSelected; }
        void setImagePushedSelected(image_t sImagePushedSelected) { ImagePushedSelected = sImagePushedSelected; }
        void setImageChosen(image_t sImageChosen) { ImageChosen = sImageChosen; }
        void setImagePushedChosen(image_t sImagePushedChosen) { ImagePushedChosen = sImagePushedChosen; }

        // gImageButton methods control functions
        void setImages(image_t sImage, image_t sImageSelected, image_t sImageChosen);
        void setImagesPushed(image_t sImagePushed, image_t sImagePushedSelected, image_t sImagePushedChosen);
        virtual void draw();
        virtual void drawBorder();

    protected:

    private:
        image_t Image;
        image_t ImageSelected;
        image_t ImageChosen;
        image_t ImagePushed;
        image_t ImagePushedSelected;
        image_t ImagePushedChosen;
};

#endif // GIMAGEBUTTON_H
