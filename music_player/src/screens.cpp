#include "screens.h"

screens::screens()
{
    Screens.reserve(SCREEN_END);
    ActiveScreen = SCREEN_END;
}

screens::~screens()
{

}

void screens::addScreen(screen_t Screen, sF_void sInitFn, sF_void sDrawFn, sF_void sExitFn, sF_void sTimeoutFn, sF_int sEventFn, int sTimeout)
{
    Screens[Screen].setInitFn(sInitFn);
    Screens[Screen].setDrawFn(sDrawFn);
    Screens[Screen].setExitFn(sExitFn);
    Screens[Screen].setTimeoutFn(sTimeoutFn);
    Screens[Screen].setEventFn(sEventFn);
    Screens[Screen].setTimeout(sTimeout);
}

void screens::goTo(screen_t Screen)
{
    sF_void Fn;

    if(ActiveScreen != SCREEN_END) {
        // execute exit function of current screen
		Fn = Screens[ActiveScreen].getExitFn();
		if(Fn != NULL) Fn();
    }
    // execute init function of new screen
    Fn = Screens[Screen].getInitFn();
	if(Fn != NULL) Fn();
	// reset update timer
	Screens[Screen].setLastDraw(0);
	// set active screen
	ActiveScreen = Screen;
}

void screens::draw()
{
    sF_void Fn;

    if(ActiveScreen != SCREEN_END) {
        Fn = Screens[ActiveScreen].getDrawFn();
        if(Fn != NULL) Fn();
        Screens[ActiveScreen].setLastDraw(time(NULL));
    }
}

void screens::forceRedraw()
{
    if(ActiveScreen != SCREEN_END) {
        Screens[ActiveScreen].setLastDraw(0);
    }
}

void screens::timeout()
{
    sF_void Fn;

    if(ActiveScreen != SCREEN_END) {
        Fn = Screens[ActiveScreen].getTimeoutFn();
        if(Fn != NULL) Fn();
    }
}

void screens::event(event_t Event)
{
    if(ActiveScreen != SCREEN_END) {
        sF_int Fn;
        // execute event function of current screen
        Fn = Screens[ActiveScreen].getEventFn();
        if(Fn != NULL) Fn(Event);
    }
}
