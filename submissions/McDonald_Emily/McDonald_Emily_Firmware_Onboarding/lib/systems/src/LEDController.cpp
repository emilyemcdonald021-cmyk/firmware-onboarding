#include "LEDController.h"

uint32_t LEDController::compute_interval_ms(float temp_c) const
{
    if (isnan(temp_c))
    {
        return m_interval_ms; // no valid reading yet: keep what we had
    }

    // Clamp the temperature into the supported range.
    if (temp_c < BMEConstants::MIN_TEMP_C) temp_c = BMEConstants::MIN_TEMP_C;
    if (temp_c > BMEConstants::MAX_TEMP_C) temp_c = BMEConstants::MAX_TEMP_C;

    // 0.0 at MIN_TEMP_C, 1.0 at MAX_TEMP_C
    float fraction = (temp_c - BMEConstants::MIN_TEMP_C) /
                     (BMEConstants::MAX_TEMP_C - BMEConstants::MIN_TEMP_C);

    float span = static_cast<float>(BMEConstants::SLOWEST_BLINK_MS -
                                    BMEConstants::FASTEST_BLINK_MS);
    float interval = static_cast<float>(BMEConstants::SLOWEST_BLINK_MS) - fraction * span;
    return static_cast<uint32_t>(interval);
}

bool LEDController::update(float temp_c, uint32_t now_ms)
{
    m_interval_ms = compute_interval_ms(temp_c);

    // Unsigned subtraction stays correct even when millis() rolls over.
    if (now_ms - m_last_toggle_ms >= m_interval_ms)
    {
        m_led_on = !m_led_on;
        m_last_toggle_ms = now_ms;
    }
    return m_led_on;
}