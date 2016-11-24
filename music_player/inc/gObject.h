#ifndef GOBJECT_H
#define GOBJECT_H

#include "lcd.h"
#include "event.h"
#include <iostream>

typedef void (*oF_void)(void);
typedef void (*oF_int)(int);

class gObject
{
    public:
        gObject();
        gObject(border_t sBorder, int sBorderWidth, color_t sBorderColor, border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected);
        virtual ~gObject();

        // gObject methods get functions
        gObject* getParent() const { return pParent; }
        int getPosX() const { return PosX; }
        int getPosY() const { return PosY; }
        int getPosXabs() const;
        int getPosYabs() const;
        int getWidth() const { return Width; }
        int getHeight() const { return Height; }
        border_t getBorder() const { return Border; }
        color_t getBorderColor() const { return BorderColor; }
        int getBorderWidth() const { return BorderWidth; }
        border_t getBorderSelected() const { return BorderSelected; }
        color_t getBorderColorSelected() const { return BorderColorSelected; }
        int getBorderWidthSelected() const { return BorderWidthSelected; }
        border_t getBorderChosen() const { return BorderChosen; }
        color_t getBorderColorChosen() const { return BorderColorChosen; }
        int getBorderWidthChosen() const { return BorderWidthChosen; }
        bool getIsSelected() const { return IsSelected; }
        bool getIsChosen() const { return IsChosen; }
        oF_int getEventFunction() const { return EventFunction; }

        // gObject methods set functions
        void setParent(gObject* Parent) { pParent = Parent; }
        void setPosX(int sPosX) { PosX = sPosX; }
        void setPosY(int sPosY) { PosY = sPosY; }
        void setWidth(int sWidth) { Width = sWidth; }
		void setHeight(int sHeight) { Height = sHeight; }
        void setBorder(border_t sBorder, int sBorderWidth, color_t sBorderColor);
        void setBorder(border_t sBorder) { Border = sBorder; }
        void setBorderColor(color_t sBorderColor) { BorderColor = sBorderColor; }
        void setBorderWidth(int sBorderWidth) { BorderWidth = sBorderWidth; }
        void setBorderSelected(border_t sBorder, int sBorderWidth, color_t sBorderColor);
        void setBorderSelected(border_t sBorderSelected) { BorderSelected = sBorderSelected; }
        void setBorderColorSelected(color_t sBorderColorSelected) { BorderColorSelected = sBorderColorSelected; }
        void setBorderWidthSelected(int sBorderWidthSelected) { BorderWidthSelected = sBorderWidthSelected; }
        void setBorderChosen(border_t sBorder, int sBorderWidth, color_t sBorderColor);
        void setBorderChosen(border_t sBorderChosen) { BorderChosen = sBorderChosen; }
        void setBorderColorChosen(color_t sBorderColorChosen) { BorderColorChosen = sBorderColorChosen; }
        void setBorderWidthChosen(int sBorderWidthChosen) { BorderWidthChosen = sBorderWidthChosen; }
        virtual void setIsSelected(bool sIsSelected) { IsSelected = sIsSelected; }
        virtual void setIsSelected() { IsSelected = true; }
        virtual void clearIsSelected() { IsSelected = false; }
        void setIsChosen(bool sIsChosen) { IsChosen = sIsChosen; }
        void setIsChosen() { IsChosen = true; }
        void clearIsChosen() { IsChosen = false; }
        void setEventFunction(oF_int sEventFunction) { EventFunction = sEventFunction; }

        // gObject methods control functions
        virtual void setStyle(border_t sBorder, int sBorderWidth, color_t sBorderColor);
        virtual void setStyleSelected(border_t sBorderSelected, int sBorderWidthSelected, color_t sBorderColorSelected);
        virtual void setStyleChosen(border_t sBorderChosen, int sBorderWidthChosen, color_t sBorderColorChosen);
        virtual void drawBorder();
        virtual void draw() = 0;
        virtual void event(event_t Event) = 0;

    protected:

    private:
        gObject* pParent;
        int PosX;
        int PosY;
        int Width;
        int Height;
        bool IsSelected;
        bool IsChosen;
        border_t Border;
        color_t BorderColor;
        int BorderWidth;
        border_t BorderSelected;
        color_t BorderColorSelected;
        int BorderWidthSelected;
        border_t BorderChosen;
        color_t BorderColorChosen;
        int BorderWidthChosen;
        oF_int EventFunction;
};

#endif // GOBJECT_H
