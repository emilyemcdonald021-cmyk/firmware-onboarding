#include "BMESPIInterface.h"

// Giving the BME280 all four pins selects the software SPI constructor.
// (Hardware SPI would take over pin 13, which is also the on-board LED.)
BMESPIInterface::BMESPIInterface()
    : m_bme(static_cast<int8_t>(BMEConstants::SPI_CS_PIN),
            static_cast<int8_t>(BMEConstants::SPI_MOSI_PIN),
            static_cast<int8_t>(BMEConstants::SPI_MISO_PIN),
            static_cast<int8_t>(BMEConstants::SPI_SCK_PIN))
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