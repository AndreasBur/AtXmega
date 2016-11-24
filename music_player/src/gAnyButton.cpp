#include "gAnyButton.h"

gAnyButton::gAnyButton()
{
    CbFunction = NULL;
    BorderPushed = BORDER_NONE;
    BorderWidthPushed = 0;
    BorderColorPushed = COLOR_NONE;
    IsPushed = false;
}

gAnyButton::~gAnyButton()
{

}

void gAnyButton::push()
{
    if(IsPushed) return;
    IsPushed = true;
    if(CbFunction != NULL) CbFunction();
}

void gAnyButton::toggle()
{
    IsPushed = !IsPushed;
    if(IsPushed) {
        if(CbFunction != NULL) CbFunction();
    }
}

void gAnyButton::setStylePushed(color_t sBackgroundColorPushed, border_t sBorderPushed, int sBorderWidthPushed, color_t sBorderColorPushed)
{
    BackgroundColorPushed = sBackgroundColorPushed;
    BorderPushed = sBorderPushed;
    BorderWidthPushed = sBorderWidthPushed;
    BorderColorPushed = sBorderColorPushed;

}

void gAnyButton::event(event_t Event)
{
    // check if event function exists
    if(getEventFunction()) {
        getEventFunction()(Event);
        return;
    }
    // default event
    if(getIsSelected()) {
        if(Event == EVENT_BUTTON1) {
            toggle();
            //clearIsChosen();
        }
        //if(Event == EVENT_BUTTON2) clearIsChosen();
    }
}
