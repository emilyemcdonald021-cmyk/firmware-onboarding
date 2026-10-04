#include "BMEI2CInterface.h"

bool BMEI2CInterface::begin()
{
    // begin() returns true if the sensor answered at that address.
    m_ready = m_bme.begin(BMEConstants::I2C_ADDRESS);
    if (!m_ready)
    {
        // Some breakout boards use the other address, so try it too.
        m_ready = m_bme.begin(BMEConstants::I2C_ADDRESS_ALT);
    }
    return m_ready;
}

float BMEI2CInterface::read_temperature()
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