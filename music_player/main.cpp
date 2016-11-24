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


/*************************************************************************************************************************************
*   P R O T O T Y P E S
*************************************************************************************************************************************/
void rotation_event(int rot_direction);
void button1_event();
void button2_event();


/**************************************************************************************
*   G L O B A L   V A R I A B L E S
***************************************************************************************/
mqd_t mq;
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

    button_init(BUTTON1_PIN, &button1_event);
    button_init(BUTTON2_PIN, &button2_event);
    encoder_init();

    Screens.addScreen(SCREEN_MAIN, init_Main, draw_Main, exit_Main, timeout_Main, event_Main, 0);
    Screens.setScreenTimout(SCREEN_MAIN, 400);

    Screens.goTo(SCREEN_MAIN);
    Screens.draw();

    musicDatabase MusicDatabase("MusicFiles.db", "MUSIC");
    //MusicDatabase.TableCreate();
    //MusicDatabase.TableAddData();
    //MusicDatabase.PrintData();
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

    while(1)
    {
        if(Screens.getScreenTimeout(Screens.getActiveScreen()) != 0) {
            Screens.timeout();
            Screens.draw();
            delay(Screens.getScreenTimeout(Screens.getActiveScreen()));
        } else {
            sleep(1);
        }
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
    if(rot_direction == 1) Screens.event(EVENT_ROTATION_R);
    if(rot_direction == -1) Screens.event(EVENT_ROTATION_L);
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
    Screens.event(EVENT_BUTTON1);
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
    Screens.event(EVENT_BUTTON2);
}
