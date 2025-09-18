#include "Component.h"

// PRIVATE

// PUBLIC
Component::Component(uint8_t pin, State state, IO io) : pin(pin) {
    gpio_init(pin);
    setIO(io);
    if (state == ON) {
        on();
    } else {
        off();
    }
}

void Component::on() {
    gpio_put(pin, true);
}

void Component::off() {
    gpio_put(pin, false);
}

void Component::setIO(Component::IO io) {
    if (io == INPUT) {
        gpio_set_dir(pin, GPIO_IN);
    } else {
        gpio_set_dir(pin, GPIO_OUT);
    }
}