#include "gButtonMenue.h"

gButtonMenue::gButtonMenue(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, orientation_t sOrientation)
{
    setParent(Parent);
    setPosX(sPosX);
    setPosY(sPosY);
    setWidth(sWidth);
    setHeight(sHeight);
    BackgroundColor = COLOR_NONE;
    Orientation = sOrientation;
    SelectedButton = 0;
    MaxButtonsOnPage = 0;
}

gButtonMenue::~gButtonMenue()
{

}

void gButtonMenue::setOrientation(orientation_t sOrientation)
{
    Orientation = sOrientation;
    calcPage();
}

int gButtonMenue::setImageButton(int Id, gImageButton sImageButton)
{
    if(Id < (int)ImageButtons.size()) {
        ImageButtons[Id] = sImageButton;
        return Id;
    }
    return -1;
}

int gButtonMenue::setTextButton(int Id, gTextButton sTextButton)
{
    if(Id < (int)TextButtons.size()) {
        TextButtons[Id] = sTextButton;
        return Id;
    }
    return -1;
}

int gButtonMenue::addButton(gImageButton Button)
{
    ImageButtons.push_back(Button);
    ButtonType.push_back(BUTTON_IMAGE);
    calcPage();
    return ImageButtons.size();
}

int gButtonMenue::addButton(gTextButton Button)
{
    TextButtons.push_back(Button);
    ButtonType.push_back(BUTTON_TEXT);
    calcPage();
    return TextButtons.size();
}

void gButtonMenue::scrollTo(int Position)
{
    if(Position >= (int)Buttons.size() || Position < 0) return;
	SelectedButton = Position;
}

void gButtonMenue::scroll(int Offset)
{
    if(Buttons.size() == 0) return;
    // clear selection of old item
    Buttons[SelectedButton]->clearIsSelected();
    //Buttons[SelectedButton]->setBackgroundColor(COLOR_NONE);
    // calculate selected Button
	SelectedButton += Offset;
	if(SelectedButton < 0) SelectedButton = Buttons.size() - 1;
    if(SelectedButton >= (int)Buttons.size()) SelectedButton = 0;
    // set selection of new Button
    Buttons[SelectedButton]->setIsSelected();
}

void gButtonMenue::draw()
{
    if(BackgroundColor != COLOR_NONE)
        LCD_DrawBox(getPosXabs(), getPosYabs(), getPosXabs()+getWidth()-1, getPosYabs()+getHeight()-1, BackgroundColor, BORDER_NONE, 0, COLOR_NONE);

    for(int i=0; i<MaxButtonsOnPage; i++)
    {
        Buttons[i]->draw();
    }

    drawBorder();
}

void gButtonMenue::event(event_t Event)
{
    if(Event == EVENT_ROTATION_R) scroll(1);
    if(Event == EVENT_ROTATION_L) scroll(-1);
    if(Event == EVENT_BUTTON1) {
        if(getIsChosen() == false) setIsChosen(true);
        else Buttons[SelectedButton]->event(Event);
    }
    if(Event == EVENT_BUTTON2) clearIsChosen();
}

void gButtonMenue::calcPageHorizontal()
{
    int ButtonWidthAll = 0;
    int Margin;

    MaxButtonsOnPage = 0;
    // get current pointer of all buttons
    getButtonPointer();
    // calculate maximal buttons
    for(int i=0; i<(int)ButtonType.size(); i++)
    {
        if(ButtonWidthAll <= getWidth()) {
            ButtonWidthAll += Buttons[i]->getWidth();
            MaxButtonsOnPage++;
        } else break;
    }
    // calculate margin for center position
    if(MaxButtonsOnPage == 0) Margin = 0;
    else Margin = (getWidth()-ButtonWidthAll)/(MaxButtonsOnPage+1);
    int PosX = Margin;
    // set PosX and PosY of Buttons for center position
    for(int i=0; i<MaxButtonsOnPage; i++)
    {
        Buttons[i]->setPosY((getHeight()/2) - (Buttons[i]->getHeight()/2));
        Buttons[i]->setPosX(PosX);
        PosX += Buttons[i]->getWidth() + Margin;
    }
}

void gButtonMenue::calcPageVertical()
{
    int ButtonHeightAll = 0;
    int Margin;

    MaxButtonsOnPage = 0;
    // get current pointer of all buttons
    getButtonPointer();
    // calculate maximal buttons
    for(int i=0; i<(int)ButtonType.size(); i++)
    {
        if(ButtonHeightAll <= getHeight()) {
            ButtonHeightAll += Buttons[i]->getHeight();
            MaxButtonsOnPage++;
        } else break;
    }
    // calculate margin for center position
    if(MaxButtonsOnPage == 0) Margin = 0;
    else Margin = (getHeight()-ButtonHeightAll)/(MaxButtonsOnPage+1);
    int PosY = Margin;
    // set PosX and PosY of Buttons for center position
    for(int i=0; i<MaxButtonsOnPage; i++)
    {
        Buttons[i]->setPosX((getWidth()/2) - (Buttons[i]->getWidth()/2));
        Buttons[i]->setPosY(PosY);
        PosY += Buttons[i]->getHeight() + Margin;
    }
}

void gButtonMenue::calcPage()
{
    if(Orientation == ORIENTATION_HORIZONTAL) {
        calcPageHorizontal();
    }
    if(Orientation == ORIENTATION_VERTICAL) {
        calcPageVertical();
    }
}

void gButtonMenue::getButtonPointer()
{
    Buttons.reserve(ButtonType.size());
    // safe the current pointer of the different button types
    for(int i=0; i<(int)ButtonType.size(); i++)
    {
        if(ButtonType[i] == BUTTON_IMAGE) {
            Buttons[i] = &ImageButtons[i];
        }
        if(ButtonType[i] == BUTTON_TEXT) {
            Buttons[i] = &TextButtons[i];
        }
    }
}
