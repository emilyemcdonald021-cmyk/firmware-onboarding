#include "BMESPIInterface.h"

// Giving the BME280 a chip-select pin selects the hardware SPI constructor.
BMESPIInterface::BMESPIInterface()
    : m_bme(static_cast<int8_t>(BMEConstants::SPI_CS_PIN))
{
}

bool BMESPIInterface::begin()
{
    m_ready = m_bme.begin();
    return m_ready;
}

float BMESPIInterface::read_temperature()
{
    if (!m_ready)
    {
        return NAN;
    }
    float t = m_bme.readTemperature(); // degrees C
    if (!isnan(t))
    {
        m_temperature_c = t;
    }
    return t;
}