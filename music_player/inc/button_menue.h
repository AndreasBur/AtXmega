#ifndef BUTTON_MENUE_H
#define BUTTON_MENUE_H

#include <vector>
#include "button.h"

typedef enum {
    POSITION_AUTO,
    POSITION_RELATIVE,
} position_t;


class button_menue
{
    public:
        button_menue();
        ~button_menue();
    protected:
    private:
        std::vector<button> Buttons;
};

#endif // BUTTON_MENUE_H
