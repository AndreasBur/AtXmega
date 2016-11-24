#include "main_screen.h"

gItemMenue *Menue1;
gItemMenue *Menue2;
gPanel *Panel;

extern struct meta smeta;

void init_Main() {
  // main menu

    Panel = new gPanel;
    std::cout << "INIT" << std::endl;
    Menue1 = new gItemMenue(10, 10, 150, 220, FONT_NORMAL, "TEST");
    Menue2 = new gItemMenue(170, 10, 100, 220, FONT_NORMAL, "TEST");
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);
    Menue1->addItem("ANDDREAS BURNICKl", COLOR_BLACK, NULL);

    Menue2->addItem("DIES IST EIN SEHR LANGER TEXT", COLOR_BLACK, NULL);
    for(int i=0; i<smeta.rows; i++)
    {
        Menue2->addItem(smeta.meta_array[i][0], COLOR_BLACK);
    }


    Panel->addObject(Menue1);
    Panel->addObject(Menue2);
}


// ---------------------------------------------------------------------------
void draw_Main() {
    std::cout << "DRAW" << std::endl;
    Panel->draw();

}


// ---------------------------------------------------------------------------
void exit_Main() {

}

void event_Main(event_t Event) {
    if(Event == EVENT_BUTTON2 && Panel->getObjectIsChosen(Panel->getSelectedObject()) == false) {
        // SCREEN_GOTO
        LCD_Text(50, 50, "SCREEN GOTO", COLOR_BLACK, COLOR_NONE, FONT_BIG);
    } else {
        Panel->event(Event);
        LCD_Clear(COLOR_WHITE);
        Panel->draw();
    }
}



