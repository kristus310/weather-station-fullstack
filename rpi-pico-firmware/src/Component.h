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
    enum IO {
        INPUT,
        OUTPUT,
    };

    Component(uint8_t pin, State state, IO io);
    void on();
    void off();
    void setIO(IO io);
};

#endif