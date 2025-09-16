#include "pico/stdlib.h"
#include "Component.h"
#include "Sensor.h"
#include "Led.h"
#include <stdio.h>

#define SENSOR_PIN 0
#define SUCCESS_LED_PIN 5
#define ERROR_LED_PIN 11

Sensor dht11(SENSOR_PIN, Component::ON);
Led successLed(SUCCESS_LED_PIN, Component::OFF);
Led errorLed(ERROR_LED_PIN, Component::OFF);

int main() {
    stdio_init_all();
    while (true) {
        sleep_ms(2000);
        Sensor::WeatherData data = dht11.read();
        if (data.error) {
            errorLed.blink();
            printf("SENSOR READ FAILED, ERROR: %d\n", dht11.getErrorMessage());
            printf("Retrying...\n");
        } else {
            successLed.blink();
            printf("Temperature: %0.1f°C, Humidity: %0.1f%%\n", data.temperature, data.humidity);
        }
    }
    return 0;
}