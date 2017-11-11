/*************************************************************************************************************************************
*   I N C L U D E
*************************************************************************************************************************************/
#include <wiringPi.h>
#include "queue.h"
#include "button_io.h"
#include "encoder_io.h"
#include "screens.h"
#include "screen_main.h"

#include "musicDatabase.h"


/*************************************************************************************************************************************
*   D E F I N E S
*************************************************************************************************************************************/
#define LOCK_DRAW   0

/*************************************************************************************************************************************
*   P R O T O T Y P E S
*************************************************************************************************************************************/
void rotation_event(int rot_direction);
void button1_event();
void button2_event();
PI_THREAD(timeout);


/**************************************************************************************
*   G L O B A L   V A R I A B L E S
***************************************************************************************/
//mqd_t mq;
screens Screens;

/*************************************************************************************************************************************
*   M A I N
*************************************************************************************************************************************/
using namespace std;
int main(int argc, char *argv[])
{
    //mq = queue_init();
    GLCD_Init(argc, argv);
    LCD_Clear(COLOR_WHITE);
    //event_t Event;

    button_init(BUTTON1_PIN, &button1_event);
    button_init(BUTTON2_PIN, &button2_event);
    encoder_init();

    Screens.addScreen(SCREEN_MAIN, init_Main, draw_Main, exit_Main, timeout_Main, event_Main, 400);

    Screens.goTo(SCREEN_MAIN);
    Screens.draw();

    //musicDatabase MusicDatabase("MusicFiles.db", "MUSIC");
    //MusicDatabase.TableCreate();
    //MusicDatabase.TableAddData();
    //MusicDatabase.PrintData();
	/*
    vector<vector<string> > MetaDaten;
    MetaDaten = MusicDatabase.getMusicMetaData(META_SORT_TITLE);
    for(int i=0; i<MetaDaten.size(); i++)
    {
        cout << "ID: " << MetaDaten[i][0] << endl;
        cout << "Title: " << MetaDaten[i][1] << endl;
        cout << "Artist: " << MetaDaten[i][2] << endl;
        cout << "Album: " << MetaDaten[i][3] << endl;
        cout << "Filename: " << MetaDaten[i][4] << endl;
    }

    MetaDaten = MusicDatabase.getMusicMetaDataSearch(META_SORT_TITLE, "Glow");
    for(int i=0; i<MetaDaten.size(); i++)
    {
        cout << "ID: " << MetaDaten[i][0] << endl;
        cout << "Title: " << MetaDaten[i][1] << endl;
        cout << "Artist: " << MetaDaten[i][2] << endl;
        cout << "Album: " << MetaDaten[i][3] << endl;
        cout << "Filename: " << MetaDaten[i][4] << endl;
    }
	*/
	if(piThreadCreate(timeout) != 0)  cout << "could not start thread" << endl;

    while(1)
    {
        sleep(1);
    }

    //queue_close(mq);

    return 0;
}


/*************************************************************************************************************************************
*
*   \fn     void rotation_event(int rot_direction)
*
*   \brief  callback function for rotation encoder
*
*   \return --
*
*************************************************************************************************************************************/
void rotation_event(int rot_direction)
{
    //if(rot_direction == 1) queue_write(mq, EVENT_ROTATION_R);
    //if(rot_direction == -1) queue_write(mq, EVENT_ROTATION_L);
    piLock(LOCK_DRAW);
    if(rot_direction == 1) Screens.event(EVENT_ROTATION_R);
    if(rot_direction == -1) Screens.event(EVENT_ROTATION_L);
    piUnlock(LOCK_DRAW);
}


/*************************************************************************************************************************************
*
*   \fn     void button1_event()
*
*   \brief  callback function for button1
*
*   \return --
*
*************************************************************************************************************************************/
void button1_event()
{
    //queue_write(mq, EVENT_BUTTON1);
    piLock(LOCK_DRAW);
    Screens.event(EVENT_BUTTON1);
    piUnlock(LOCK_DRAW);
}


/*************************************************************************************************************************************
*
*   \fn     void button2_event()
*
*   \brief  callback function for button2
*
*   \return --
*
*************************************************************************************************************************************/
void button2_event()
{
    //queue_write(mq, EVENT_BUTTON2);
    piLock(LOCK_DRAW);
    Screens.event(EVENT_BUTTON2);
    piUnlock(LOCK_DRAW);
}


/*************************************************************************************************************************************
*
*   \fn     PI_THREAD(timeout)
*
*   \brief  thread for timeout handling
*
*   \return --
*
*************************************************************************************************************************************/
PI_THREAD(timeout)
{
    (void)piHiPri(55);

    while(1)
    {
        if(Screens.getScreenTimeout(Screens.getActiveScreen()) != 0) {
            piLock(LOCK_DRAW);
            Screens.event(EVENT_TIMEOUT);
            piUnlock(LOCK_DRAW);
            delay(Screens.getScreenTimeout(Screens.getActiveScreen()));
        } else {
            sleep(1);
        }
    }
    return 0;
}

