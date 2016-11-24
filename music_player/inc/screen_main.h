#ifndef _SCREEN_MAIN_H_
#define _SCREEN_MAIN_H_

#include <vector>
#include <iostream>
#include "event.h"
#include "gObject.h"
#include "gPanel.h"
#include "gItem.h"
#include "gImageButton.h"
#include "gTextButton.h"
#include "gTextItem.h"
#include "gItemMenue.h"
#include "screens.h"
#include "gButtonMenue.h"

//gPanel* pPanel;
//gTextButton* pTextButton1;
//gImageButton* pImageButton1;

void init_Main();
void draw_Main();
void exit_Main();
void timeout_Main();
void event_Main(event_t Event);


#endif
