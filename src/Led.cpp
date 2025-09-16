#include "Led.h"
#include "Component.h"
#include "pico/stdlib.h"

// PRIVATE

// PUBLIC
Led::Led(uint8_t pin, State state) : Component(pin, state) {}

void Led::blink() {
    on();
    sleep_ms(300);
    off();
}