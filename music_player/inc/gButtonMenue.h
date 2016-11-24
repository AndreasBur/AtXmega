#ifndef GBUTTONMENUE_H
#define GBUTTONMENUE_H

#include <vector>
#include "gAnyMenue.h"
#include "gAnyButton.h"
#include "gImageButton.h"
#include "gTextButton.h"

typedef enum {
    BUTTON_IMAGE,
    BUTTON_TEXT
} button_t;

typedef enum {
    ORIENTATION_VERTICAL,
    ORIENTATION_HORIZONTAL
} orientation_t;

class gButtonMenue : public gAnyMenue
{
    public:
        gButtonMenue(gObject* Parent, int sPosX, int sPosY, int sWidth, int sHeight, orientation_t sOrientation);
        virtual ~gButtonMenue();

        //gButtonMenue methods get functions
        std::vector<gAnyButton*> getButtons() const { return Buttons; }
        std::vector<gImageButton> getImageButtons() const { return ImageButtons; }
        std::vector<gTextButton> getTextButtons() const { return TextButtons; }
        color_t getBackgroundColor() const { return BackgroundColor; }
        orientation_t getOrientation() const { return Orientation; }
        int getSelectedButton() const { return SelectedButton; }
        // gButtonMenue methods set functions
        void setBackgroundColor(color_t sBackgroundColor) { BackgroundColor = sBackgroundColor; }
        void setOrientation(orientation_t sOrientation);
        //void setButtons(std::vector<gAnyButton*> sButtons) { Buttons = sButtons; }
        //void setImageButtons(std::vector<gImageButton> sImageButtons) { ImageButtons = sImageButtons; }
        //void setTextButtons(std::vector<gTextButton> sTextButtons) { TextButtons = sTextButtons; }

        // gButton methods get functions
        gAnyButton* getpButton(int Id) { return Buttons[Id]; }
        gImageButton getImageButton(int Id) const { return ImageButtons[Id]; }
        gImageButton& getrImageButton(int Id) { return ImageButtons[Id]; }
        gTextButton getTextButton(int Id) const { return TextButtons[Id]; }
        gTextButton& getrTextButton(int Id) { return TextButtons[Id]; }
        // gButton methods set functions
        int setImageButton(int Id, gImageButton sImageButtons);
        int setTextButton(int Id, gTextButton sTextButtons);

        // gButton methods
        int addButton(gImageButton Button);
        int addButton(gTextButton Button);

		// gButtonMenue methods control functions
        void scroll(int Offset);
        void scrollTo(int position);
        void timeout();
        virtual void draw();
        virtual void event(event_t Event);

    protected:

    private:
        void calcPage();
        void calcPageHorizontal();
        void calcPageVertical();
        void getButtonPointer();
        std::vector<gAnyButton*> Buttons;
        std::vector<gImageButton> ImageButtons;
        std::vector<gTextButton> TextButtons;
        std::vector<button_t> ButtonType;
        color_t BackgroundColor;
        orientation_t Orientation;
        int SelectedButton;
        int MaxButtonsOnPage;
};

#endif // GBUTTONMENUE_H
