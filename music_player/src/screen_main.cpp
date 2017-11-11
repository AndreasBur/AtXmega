#include "screen_main.h"

//extern screens Screens;
gPanel* pPanel;
gTextButton* pTextButton1;
gImageButton* pImageButton1;
gTextItem* pItem1;
gTextItem* pItem2;
gItem* pItem;
gItemMenue* pItemMenue;
gButtonMenue* pButtonMenue;

void init_Main() {
  // main menu
    pPanel = new gPanel;

    pImageButton1 = new gImageButton(pPanel, 50, 50, 30, 30, IMAGE_REPEAT, IMAGE_REPEAT_PUSHED);
    pImageButton1->setStyle(BORDER_RECT, 3, COLOR_BLUE2);
    pImageButton1->setStyleSelected(BORDER_CIRCLE, 3, COLOR_RED);

    pTextButton1 = new gTextButton(pPanel, 250, 150, 70, 50);
    pTextButton1->setStyle(COLOR_YELLOW, "Button", FONT_BIG, BORDER_RECT_ROUNDED, 3, COLOR_BLACK);
    pTextButton1->setStyleSelected(BORDER_RECT, 3, COLOR_RED);
    pTextButton1->setStylePushed(COLOR_GREEN, "pushed", FONT_NORMAL, BORDER_RECT, 3, COLOR_BLACK);
    pTextButton1->setTextAlign(ALIGN_CENTER);

    pItem1 = new gTextItem(pPanel, 10, 200, 150, 30);
    pItem1->setStyle(COLOR_YELLOW, "WAS GEHT AB JO MAN TEST TEST", FONT_BIG, COLOR_BLACK, BORDER_NONE, 0, COLOR_NONE);
    pItem1->setBorderSelected(BORDER_RECT, 3, COLOR_RED);
    //pItem->setBorder(BORDER_RECT, 2, COLOR_BLACK);
    pItem2 = new gTextItem(pPanel, 180, 170, 100, 45);
    pItem2->setStyle(COLOR_YELLOW, "EIN GANZ anderer Text", FONT_BIG, COLOR_BLACK, BORDER_NONE, 0, COLOR_NONE);
    pItem2->setBorderSelected(BORDER_RECT, 2, COLOR_BLUE2);
    pItem2->setTextAlign(ALIGN_CENTER);

    pItem = new gItem(pPanel, 10, 130, 200, 40);
    //pItem->setImage(IMAGE_REPEAT, 30, 30, 10, 10);
    pItem->setText("TEST EIN SEHR LANGER TEXT ZU LANG FUER DIE ANZEIGE", FONT_NORMAL, COLOR_BLACK);
    pItem->setBorder(BORDER_RECT, 2, COLOR_RED);
    pItem->setBackgroundColor(COLOR_GREEN);
    pItem->setWidth(100);


    pItemMenue = new gItemMenue(pPanel, 10, 10, 300, 220, FONT_EXTREME_BIG, "MAIN MENUE");
    pItemMenue->addItem("PLAY MUSIC Andreas Burnickl", IMAGE_MUSIC, 30, 24, 10, 10, COLOR_BLACK, NULL);
    pItemMenue->addItem("SHOUTCAST", IMAGE_MUSIC, 30, 24, 10, 10, COLOR_BLACK, NULL);
    pItemMenue->addItem("MUSIC LIBRARY", IMAGE_MUSIC, 30, 24, 10, 10, COLOR_BLACK, NULL);
    pItemMenue->addItem("SETTINGS", IMAGE_MUSIC, 30, 24, 10, 10, COLOR_BLACK, NULL);

    pItemMenue->setBorder(BORDER_RECT_ROUNDED, 3, COLOR_BLUE2);
    pItemMenue->setBorderSelected(BORDER_RECT, 3, COLOR_RED);
    pItemMenue->setBorderChosen(BORDER_RECT_ROUNDED, 3, COLOR_BLUE2);
    pItemMenue->setItemMargin(5);
    //pItemMenue->setItemLines(true);

    pButtonMenue = new gButtonMenue(pPanel, 30, 30, 40, 200, ORIENTATION_VERTICAL);
    pButtonMenue->setBorder(BORDER_RECT, 3, COLOR_BLACK);
    gTextButton Button(pButtonMenue, 0, 5, 35, 20);
    Button.setBorder(BORDER_RECT, 3, COLOR_BLACK);
    gTextButton Button2(pButtonMenue, 40, 5, 15, 20);
    Button2.setBorder(BORDER_RECT, 3, COLOR_BLACK);
    gTextButton Button3(pButtonMenue, 80, 5, 25, 33);
    Button3.setBorder(BORDER_RECT, 3, COLOR_BLACK);

    pButtonMenue->addButton(Button);
    pButtonMenue->addButton(Button2);
    pButtonMenue->addButton(Button3);
    //pButtonMenue->addButton(gTextButton(pButtonMenue, 80, 5, 25, 33));

/*
    gItem* pItem3 = new gItem(pPanel, 10,10, 10, 10);
    pItem3->setText("Hallo", FONT_BIG, COLOR_BLACK);
    gItem* pItem4 = new gItem(pItem3, 10, 10, 10, 10);
    pItem4->setText("Hallo", FONT_BIG, COLOR_BLACK);
    gItem* pItem5 = new gItem(pItem4, 30, 10, 10, 10);
    pItem5->setText("Hallo", FONT_BIG, COLOR_BLACK);


    gItem Item3(pPanel, 10,10, 100, 100);
    Item3.setText("Hallo", FONT_BIG, COLOR_BLACK);
    gItem Item4(&Item3, 10, 10, 100, 100);
    Item4.setText("Hallo", FONT_BIG, COLOR_BLACK);
    gItem Item5(&Item4, 30, 10, 100, 100);
    Item5.setText("Hallo", FONT_BIG, COLOR_BLACK);

    std::cout << "Item3:" << Item3.getPosXabs() << std::endl;
    std::cout << "Item4:" << Item4.getPosXabs() << std::endl;
    std::cout << "Item5:" << Item5.getPosXabs() << std::endl;
*/
/*
    gItem Item10(pPanel, 25, 25, 100, 29);
    Item10.setPosY(100);
    Item10.setPosX(50);
    Item10.setBorder(BORDER_RECT, 3, COLOR_BLACK);
    Item10.setText("HALLO", FONT_NORMAL, COLOR_BLACK);
    //Item10.draw();

    std::vector<gItem> Items;
    Items.push_back(Item10);
    Items.at(0).setPosY(150);
    Items.at(0).draw();
*/
    //std::cout << pItemMenue->getItem(0).getPosXabs() << std::endl;

    //pPanel->addObject(pImageButton1);
    //pPanel->addObject(pTextButton1);
    //pPanel->addObject(pItem3);
    //pPanel->addObject(pItem4);
    //pPanel->addObject(pItem5);
    //pPanel->addObject(pItem);
    pPanel->addObject(pItemMenue);
    //pPanel->addObject(pButtonMenue);

}

void draw_Main() {
    //LCD_Clear(COLOR_WHITE);
    pPanel->draw();
}

void exit_Main() {

}

void timeout_Main() {
    //pItem1->timeout();
    //pItem2->timeout();
    //pItem->timeout();
    pItemMenue->timeout();
    //draw_Main();
}

void event_Main(event_t Event) {
    if(Event == EVENT_BUTTON2 && pPanel->getpObject(pPanel->getSelectedObject())->getIsChosen() == false) {
        // SCREEN_GOTO
        LCD_Text(50, 50, "SCREEN GOTO", COLOR_BLACK, COLOR_NONE, FONT_BIG);
    } else {
        if(Event == EVENT_TIMEOUT) timeout_Main();
        else pPanel->event(Event);
        draw_Main();
    }
}
