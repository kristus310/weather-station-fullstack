#include "Component.h"
#include "Led.h"
#include "Sensor.h"
#include "pico/stdlib.h"
#include <cstring>
#include <stdio.h>

#define SENSOR_PIN 0
#define SUCCESS_LED_PIN 5
#define ERROR_LED_PIN 11

Sensor dht11(SENSOR_PIN, Component::ON, Component::OUTPUT);
Led successLed(SUCCESS_LED_PIN, Component::OFF, Component::OUTPUT);
Led errorLed(ERROR_LED_PIN, Component::OFF, Component::OUTPUT);

int main() {
    stdio_init_all();
    while (true) {
        sleep_ms(2000);
        Sensor::WeatherData data = dht11.read();
        if (data.errorMessage && strcmp(data.errorMessage, "NULL") != 0) {
            errorLed.blink();
            dht11.printError(data);
        }
        else {
            successLed.blink();
            dht11.printData(data);
        }
    }
    return 0;
}