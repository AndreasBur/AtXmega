#ifndef GIMAGEITEM_H
#define GIMAGEITEM_H

#include "gObject.h"
#include "images.h"

class gImageItem : public gObject
{
    public:
        gImageItem();
        gImageItem(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, image_t sImage);
        virtual ~gImageItem();

        // gImageItem methods get functions
        image_t getImage() const { return Image; }
        image_t getImageSelected() const { return ImageSelected; }
        image_t getImageChosen() const { return ImageChosen; }
        // gImageItem methods set functions
        void setImage(image_t sImage) { Image = sImage; }
        void setImageSelected(image_t sImageSelected) { ImageSelected = sImageSelected; }
        void setImageChosen(image_t sImageChosen) { ImageChosen = sImageChosen; }

        // gImageItem methods control functions
        virtual void draw();
        virtual void event(event_t Event);
    protected:

    private:
        image_t Image;
        image_t ImageSelected;
        image_t ImageChosen;
};

#endif // GIMAGEITEM_H
