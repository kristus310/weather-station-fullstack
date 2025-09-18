#include "Sensor.h"
#include "Component.h"
#include <stdio.h>

// PRIVATE
bool Sensor::waitForSignalState(bool state, uint32_t timeout_us) {
    uint32_t start = time_us_32();
    while (gpio_get(pin) != state) {
        if ((time_us_32() - start) > timeout_us) {
            return false;
        }
    }
    return true;
}

// PUBLIC
Sensor::Sensor(uint8_t pin, State state, IO io) : Component(pin, state, io) {}

void Sensor::sendData(Sensor::WeatherData data) {
    printf("%0.1f,%0.1f\n", data.temperature, data.humidity);
}

Sensor::WeatherData Sensor::read() {
    result = {0, 0, true}; // initialiazing the result
    uint8_t bytes[5] = {0};

    int startingSignal = 20;        // "at least 18ms for starting signal" - DHT11 datasheet
    int waitingSignal = 40;         //" 20-40us for waiting signal" - DHT11 datasheet
    setIO(OUTPUT);
    off();                          // Pulling low voltage level
    sleep_ms(startingSignal);       // Waiting for the sensor to detect the output
    on();                           // Pulling high voltage level
    sleep_us(waitingSignal);        // Now the Pico is waiting for the response
    setIO(INPUT);                  // Now setting the gpio pin to be an input
    gpio_pull_up(pin);
    // Waiting for the sensor response
    int signalResponseCount = 3;
    // 1. for a low signal
    // 2. for high signal
    // 3. for low signal again
    if (!waitForSignalState(false, 200) || !waitForSignalState(true, 200) || !waitForSignalState(false, 200)) {
        return result;
    }

    int bits = 40; // The sensor sends the MCU, 5 bytes = 40 bits!
    for (int i = 0; i < bits; i++) {
        if (!waitForSignalState(true, 200)) {
            return result;
        }
        uint32_t start = time_us_32();
        if (!waitForSignalState(false, 200)) {
            return result;
        }
        uint32_t duration = time_us_32() - start;
        uint32_t longPulse = 35; // If pulse > ~35us, it's a '1', otherwise it's a '0'
        bytes[i / 8] <<= 1; // Just turning the data to bytes
        if (duration > longPulse) {
            bytes[i / 8] |= 1;
        }
    }

    uint8_t sum = bytes[0] + bytes[1] + bytes[2] + bytes[3];
    if (sum != bytes[4]) { // the last byte is reserved for error checking and it is the sum of every other byte.
        return result;
    }

    result.humidity = (float)bytes[0] + (float)bytes[1] * 0.1f;
    result.temperature = (float)bytes[2] + (float)bytes[3] * 0.1f;
    result.error = false;
    return result;
}