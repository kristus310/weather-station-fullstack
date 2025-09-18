#ifndef SENSOR_H
#define SENSOR_H

#include "pico/stdlib.h"
#include "Component.h"

class Sensor : public Component {
public:
    struct WeatherData {
        float temperature;
        float humidity;
        char errorMessage[20];
    };

    Sensor(uint8_t pin, State state, IO io);
    void printData(WeatherData data);
    void printError(WeatherData data);
    WeatherData read();

private:
    Sensor::WeatherData result;
    bool waitForSignalState(bool state, uint32_t timeout_us);
};

#endif