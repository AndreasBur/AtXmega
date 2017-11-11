#include "screen.h"

screen::screen()
{
    InitFn = NULL;
    DrawFn = NULL;
    ExitFn = NULL;
    TimeoutFn = NULL;
    EventFn = NULL;
    Timeout = 0;
    LastDraw = 0;
}

screen::screen(sF_void sInitFn, sF_void sDrawFn, sF_void sExitFn, sF_void sTimeoutFn, sF_int sEventFn)
{
    InitFn = sInitFn;
    DrawFn = sDrawFn;
    ExitFn = sExitFn;
    TimeoutFn = sTimeoutFn;
    EventFn = sEventFn;
    Timeout = 0;
    LastDraw = 0;
}

screen::~screen()
{

}
