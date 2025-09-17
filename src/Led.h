#ifndef LED_H
#define LED_H

#include "Component.h"

class Led : public Component {
private:

public:
    Led(uint8_t pin, State state, IO io);
    void blink();
};

#endif