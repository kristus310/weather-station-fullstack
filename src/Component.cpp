#include "Component.h"

// PRIVATE

// PUBLIC
Component::Component(uint8_t pin, State state) : pin(pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
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