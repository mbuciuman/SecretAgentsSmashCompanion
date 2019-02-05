#ifndef GCTRAIN_CONSTANTS_H_
#define GCTRAIN_CONSTANTS_H_

#include <stdint.h>
#include <Arduino.h>

enum class Direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN
};

// Pin definitions
const int PIN_LED = LED_BUILTIN;
const int CONTROLLER_DATA_PIN = 3;
const int CONSOLE_DATA_PIN = 5;

// according to 'Yet Another Gamecube Documentation.htm', min/max values for axis
const uint8_t MIN_AXIS_VAL = 32;
const uint8_t MAX_AXIS_VAL = 234;
const uint8_t AVG_AXIS_VAL = 127;

#endif // GCTRAIN_CONSTANTS_H_