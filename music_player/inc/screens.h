#ifndef SCREENS_H
#define SCREENS_H

#include <vector>
#include "screen.h"
#include "event.h"

typedef enum {
	SCREEN_MAIN,
	SCREEN_MUSIC,
	SCREEN_PLAY,
	SCREEN_END
} screen_t;

class screens
{
    public:
        screens();
        ~screens();

        // screens get functions
        screen_t getActiveScreen() const { return ActiveScreen; }
        // screens set functions
        //void setActiveScreen(screen_t sActiveScreen) { ActiveScreen = sActiveScreen; }
        // screens functions
        void addScreen(screen_t Screen, sF_void sInitFn, sF_void sDrawFn, sF_void sExitFn, sF_void sTimeoutFn, sF_int sEventFn, int sTimeout=0);

        // screen methods get functions
        screen getScreen(screen_t Screen) const { return Screens[Screen]; }
        sF_void getScreenInitFn(screen_t Screen) const { return Screens[Screen].getInitFn(); }
        sF_void getScreenDrawFn(screen_t Screen) const { return Screens[Screen].getDrawFn(); }
        sF_void getScreenExitFn(screen_t Screen) const { return Screens[Screen].getExitFn(); }
        sF_void getScreenTimeoutFn(screen_t Screen) const { return Screens[Screen].getTimeoutFn(); }
        sF_int getScreenEventFn(screen_t Screen) const { return Screens[Screen].getEventFn(); }
        int getScreenTimeout(screen_t Screen) const { return Screens[Screen].getTimeout(); }
        int getNumberOfScreens() const { return SCREEN_END; }
        // screen methods set functions
        void setScreen(screen_t Screen, screen sScreen) { Screens[Screen] =  sScreen; }
        void setScreenInitFn(screen_t Screen, sF_void sInitFn) { Screens[Screen].setInitFn(sInitFn); }
        void setScreenDrawFn(screen_t Screen, sF_void sDrawFn) { Screens[Screen].setDrawFn(sDrawFn); }
        void setScreenExitFn(screen_t Screen, sF_void sExitFn) { Screens[Screen].setExitFn(sExitFn); }
        void setScreenTimeoutFn(screen_t Screen, sF_void sTimeoutFn) { Screens[Screen].setTimeoutFn(sTimeoutFn); }
        void setScreenEventFn(screen_t Screen, sF_int sEventFn) { Screens[Screen].setEventFn(sEventFn); }
        void setScreenTimout(screen_t Screen, int sTimeout) { Screens[Screen].setTimeout(sTimeout); }

        // screens control functions
        void draw();
        void goTo(screen_t Screen);
        void forceRedraw();
        void timeout();
        void event(event_t Event);

    protected:

    private:
        std::vector<screen> Screens;
        screen_t ActiveScreen;
};

#endif // SCREENS_H
