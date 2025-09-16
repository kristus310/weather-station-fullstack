#ifndef COMPONENT_H
#define COMPONENT_H

#include "pico/stdlib.h"

class Component {
protected:
    uint8_t pin;

public:
    enum State {
        ON,
        OFF,
    };
    Component(uint8_t pin, State state);
    void on();
    void off();
};

#endif