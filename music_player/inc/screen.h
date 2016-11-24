#ifndef SCREEN_H
#define SCREEN_H

#include <time.h>
#include "event.h"

typedef void (*sF_void) (void);
typedef void (*sF_int) (event_t);

class screen
{
    public:
        screen();
        screen(sF_void sInitFn, sF_void sDrawFn, sF_void sExitFn, sF_void sTimeoutFn, sF_int sEventFn);
        ~screen();

        // screen methods get functions
        sF_void getInitFn() const { return InitFn; }
        sF_void getDrawFn() const { return DrawFn; }
        sF_void getExitFn() const { return ExitFn; }
        sF_void getTimeoutFn() const { return TimeoutFn; }
        sF_int getEventFn() const { return EventFn; }
        int getTimeout() const { return Timeout; }
        time_t getLastDraw() const { return LastDraw; }
        // screen methods set functions
        void setInitFn(sF_void sInitFn) { InitFn = sInitFn; }
        void setDrawFn(sF_void sDrawFn) { DrawFn = sDrawFn; }
        void setExitFn(sF_void sExitFn) { ExitFn = sExitFn; }
        void setTimeoutFn(sF_void sTimeoutFn) { TimeoutFn = sTimeoutFn; }
        void setEventFn(sF_int sEventFn) { EventFn = sEventFn; }
        void setTimeout(int sTimeout) { Timeout = sTimeout; }
        void setLastDraw(time_t sLastDraw) { LastDraw = sLastDraw; }

    protected:

    private:
        sF_void InitFn;
        sF_void DrawFn;
        sF_void ExitFn;
        sF_void TimeoutFn;
        sF_int EventFn;
        int Timeout;
        time_t LastDraw;
};

#endif // SCREEN_H
