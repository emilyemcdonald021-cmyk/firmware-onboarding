#pragma once
#include <Arduino.h>
#include <etl/singleton.h>
#include "BMEConstants.h"

// System: all the logic. It only knows "a temperature number in, LED state out".
// It has no idea where the temperature came from (I2C, SPI, or anything else).
class LEDController
{
public:
    LEDController() = default;

    // Warmer -> shorter interval (faster blink). Linear between MIN and MAX temp,
    // clamped outside that range. A NAN temperature keeps the current interval.
    uint32_t compute_interval_ms(float temp_c) const;

    // Call every loop. Returns whether the LED should be ON right now.
    bool update(float temp_c, uint32_t now_ms);

private:
    uint32_t m_interval_ms = BMEConstants::SLOWEST_BLINK_MS;
    uint32_t m_last_toggle_ms = 0;
    bool m_led_on = false;
};

using LEDControllerInstance = etl::singleton<LEDController>;