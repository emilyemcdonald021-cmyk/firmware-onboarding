#include <Arduino.h>
#include "BMEI2CInterface.h"
#include "LEDController.h"
#include "BMEConstants.h"

void setup()
{
    Serial.begin(BMEConstants::SERIAL_BAUD);
    pinMode(BMEConstants::LED_PIN, OUTPUT);

    // Create the single instance of each class.
    BMEI2CInterfaceInstance::create();
    LEDControllerInstance::create();

    if (BMEI2CInterfaceInstance::instance().begin())
    {
        Serial.println(F("BME280 found"));
    }
    else
    {
        Serial.println(F("ERROR: BME280 not found. Check wiring/address/CS pin."));
    }
}

void loop()
{
    static uint32_t lastPollMs = 0;
    static uint32_t lastRetryMs = 0;
    static float temperatureC = NAN;

    uint32_t now = millis();
    BMEI2CInterface& sensor = BMEI2CInterfaceInstance::instance();

    // Sensor missing: keep LED off and retry periodically (no delay()).
    if (!sensor.is_ready())
    {
        digitalWrite(BMEConstants::LED_PIN, LOW);
        if (now - lastRetryMs >= BMEConstants::RETRY_MS)
        {
            lastRetryMs = now;
            if (sensor.begin())
            {
                Serial.println(F("BME280 found"));
            }
            else
            {
                Serial.println(F("ERROR: BME280 not found. Check wiring/address/CS pin."));
            }
        }
        return;
    }

    // Read the sensor on a fixed schedule.
    if (now - lastPollMs >= BMEConstants::SENSOR_POLL_MS)
    {
        lastPollMs = now;
        float t = sensor.read_temperature();
        if (!isnan(t))
        {
            temperatureC = t;
            Serial.print(F("Temp C: "));
            Serial.println(temperatureC);
        }
    }

    // The system decides the LED state; main just drives the pin.
    bool ledOn = LEDControllerInstance::instance().update(temperatureC, now);
    digitalWrite(BMEConstants::LED_PIN, ledOn ? HIGH : LOW);
}