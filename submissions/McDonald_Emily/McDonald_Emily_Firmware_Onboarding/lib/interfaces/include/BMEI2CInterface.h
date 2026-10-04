#pragma once
#include <Adafruit_BME280.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

// Interface: talks to the BME280 over I2C and stores the data.
// No decisions or logic here, only communicate and collect.
class BMEI2CInterface
{
public:
    BMEI2CInterface() = default;

    // Connects to the sensor. Returns false if it isn't found (wiring/address problem).
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

using BMEI2CInterfaceInstance = etl::singleton<BMEI2CInterface>;