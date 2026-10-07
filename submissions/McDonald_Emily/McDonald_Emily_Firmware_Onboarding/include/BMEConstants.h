#pragma once
#include <Arduino.h>

// Shared constants for the whole project. Change a value here once and
// every file that uses it stays correct.
namespace BMEConstants
{
    // ---- CONFIRM THESE 3 WITH THE SHOP (they depend on their wiring) ----
    constexpr uint8_t I2C_ADDRESS = 0x76;     // BME280 I2C address (0x76 or 0x77)
    constexpr uint8_t SPI_CS_PIN = 10;        // chip-select pin for the SPI build
    constexpr uint8_t LED_PIN = LED_BUILTIN;  // on-board "L" LED (pin 13 on the Uno)
    // ---------------------------------------------------------------------

    // SPI data pins. Same as the Uno's hardware SPI pins, but the SPI build uses
    // software SPI so pin 13 (SCK) can double as the on-board LED.
    constexpr uint8_t SPI_MOSI_PIN = 11;
    constexpr uint8_t SPI_MISO_PIN = 12;
    constexpr uint8_t SPI_SCK_PIN = 13;

    constexpr uint8_t I2C_ADDRESS_ALT = 0x77; // fallback address tried if the first fails

    constexpr unsigned long SERIAL_BAUD = 115200; // matches monitor_speed in platformio.ini

    // Temperature range that maps to the blink range (degrees C)
    constexpr float MIN_TEMP_C = 15.0f;       // at/below this: slowest blink
    constexpr float MAX_TEMP_C = 35.0f;       // at/above this: fastest blink

    // Blink interval range (milliseconds between LED toggles)
    constexpr uint32_t SLOWEST_BLINK_MS = 1000;
    constexpr uint32_t FASTEST_BLINK_MS = 100;

    // Timing (all non-blocking, using millis() instead of delay())
    constexpr uint32_t SENSOR_POLL_MS = 500;  // how often to read the sensor
    constexpr uint32_t RETRY_MS = 2000;       // how often to retry if sensor not found
}