#ifndef SENSOR_H
#define SENSOR_H

#include "pico/stdlib.h"
#include "Component.h"

class Sensor : public Component {
private:
    char errorMessage[50];
    bool waitForSignalState(bool state, uint32_t timeout_us);

public:
    struct WeatherData {
        float temperature;
        float humidity;
        char error;
    };

    Sensor(uint8_t pin, State state);
    const char* getErrorMessage() const;
    WeatherData read();
};

#endif