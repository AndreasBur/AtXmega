#ifndef GITEM_H
#define GITEM_H

#include "gObject.h"
#include "gImageItem.h"
#include "gTextItem.h"

class gItem : public gObject
{
    public:
        gItem();
        gItem(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight);
        virtual ~gItem();
        gItem(const gItem& rhs);
        gItem& operator=(const gItem& rhs);

        // gItem methods get functions
        color_t getBackgroundColor() const { return BackgroundColor; }
        gImageItem* getpImageItem() { return pImageItem; }
        gImageItem getImageItem() const { return *pImageItem; }
        gTextItem* getpTextItem() { return pTextItem; }
        gTextItem getTextItem() const { return *pTextItem; }
        int getImageMarginLeft() const { return ImageMarginLeft; }
        int getImageMarginRight() const { return ImageMarginRight; }
        bool getTimeout() const { return Timeout; }
        // gItem methods set functions
        void setWidth(int sWidth);
        void setBackgroundColor(color_t sBackgroundColor) { BackgroundColor = sBackgroundColor; }
        void setImageItem(gImageItem* sImageItem) { pImageItem = sImageItem; }
        void setTextItem(gTextItem* sTextItem) { pTextItem = sTextItem; }
        void setImageMarginLeft(int sImageMarginLeft) { ImageMarginLeft = sImageMarginLeft; }
        void setImageMarginRight(int sImageMarginRight) { ImageMarginRight = sImageMarginRight; }
        void setTimeout(bool sTimeout) { Timeout = sTimeout; }
        virtual void setIsSelected(bool sIsSelected);
        virtual void setIsSelected();
        virtual void clearIsSelected();

        // gItem methods control functions
        void setImage(image_t Image, int Width, int Height, int MarginRight=0, int MarginLeft=0);
        void setText(std::string Text, font_t Font, color_t TextColor);
        void timeout();
        virtual void draw();
        virtual void event(event_t Event);

    protected:

    private:
        color_t BackgroundColor;
        gImageItem* pImageItem;
        gTextItem* pTextItem;
        int ImageMarginLeft;
        int ImageMarginRight;
        bool Timeout;
};

#endif // GITEM_H
