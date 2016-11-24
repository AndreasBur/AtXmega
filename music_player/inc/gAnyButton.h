#ifndef GANYBUTTON_H
#define GANYBUTTON_H

#include "gObject.h"


class gAnyButton : public gObject
{
    public:
        gAnyButton();
        virtual ~gAnyButton();

        // gAnyButton methods get functions
        color_t getBackgroundColor() const { return BackgroundColor; }
        color_t getBackgroundColorPushed() const { return BackgroundColorPushed; }
        border_t getBorderPushed() const { return BorderPushed; }
        int getBorderWidthPushed() const { return BorderWidthPushed; }
        color_t getBorderColorPushed() const { return BorderColorPushed; }
        oF_void getCbFunction() const { return CbFunction; }
        bool getIsPushed() const { return IsPushed; }
        // gAnyButton methods set functions
        void setBackgroundColor(color_t sBackgroundColor) { BackgroundColor = sBackgroundColor; }
        void setBackgroundColorPushed(color_t sBackgroundColorPushed) { BackgroundColorPushed = sBackgroundColorPushed; }
        void setBorderPushed(border_t sBorderPushed) { BorderPushed = sBorderPushed; }
        void setBorderWidthPushed(int sBorderWidthPushed) { BorderWidthPushed = sBorderWidthPushed; }
        void setBorderColorPushed(color_t sBorderColorPushed) { BorderColorPushed = sBorderColorPushed; }
        void setCbFunction(oF_void sCbFunction) { CbFunction = sCbFunction; }
        void setIsPushed(bool sIsPushed) { IsPushed = sIsPushed; }
        void setIsPushed() { IsPushed = true; }
        void clearIsPushed() { IsPushed = false; }

        // gTextButton methods control functions
        void push();
        void release() { IsPushed = false; }
        void toggle();
        virtual void setStylePushed(color_t sBackgroundColorPushed, border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed);
        virtual void event(event_t Event);
    protected:

    private:
        color_t BackgroundColor;
        color_t BackgroundColorPushed;
        border_t BorderPushed;
        int BorderWidthPushed;
        color_t BorderColorPushed;
        oF_void CbFunction;
        bool IsPushed;
};

#endif // GANYBUTTON_H
