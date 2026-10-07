#pragma once
#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

// Interface: talks to the BME280 over SPI and stores the data.
// Uses software SPI on pins CS=10, MOSI=11, MISO=12, SCK=13 (see BMEConstants.h)
// so that pin 13 stays free to drive the on-board LED.
class BMESPIInterface
{
public:
    BMESPIInterface();

    // Connects to the sensor. Returns false if it isn't found (wiring problem).
    bool begin();

    // Reads the sensor, stores the value, and returns temperature in C.
    // Returns NAN if the sensor isn't ready.
    float read_temperature();

    float get_temperature() const { return m_temperature_c; }
    bool is_ready() const { return m_ready; }

private:
    Adafruit_BME280 m_bme;
    float m_temperature_c = NAN;
    bool m_ready = false;
};

using BMESPIInterfaceInstance = etl::singleton<BMESPIInterface>;