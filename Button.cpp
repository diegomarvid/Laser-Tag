#include "Button.h"

Button::Button(int aPin)
{
    pin = aPin;
    pinMode(pin, INPUT);
}

bool Button::IsReleased()
{
    buttonState = digitalRead(pin);

    if(buttonState == PRESSED)
    {
        while(buttonState) buttonState = digitalRead(pin);
            
        delay(50);

        return true;
     }

     return false;
}

