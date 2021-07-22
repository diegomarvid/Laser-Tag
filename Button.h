#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{   
    static const bool PRESSED = 1;

    int pin;
    int buttonState;

    public:
        Button(int aPin);
        bool IsReleased();

};

#endif