#ifndef GCTRAIN_CONSTANTS_HPP_
#define GCTRAIN_CONSTANTS_HPP_

#include <Arduino.h>
#include <stdint.h>

enum class Direction : uint8_t { LEFT, UP, RIGHT, DOWN, NO_DIR };
enum class ControllerInput : uint8_t {
    A = 0,
    B,
    X,
    Y,
    L,
    L_ANALOG,
    R,
    R_ANALOG,
    Z,
    XAXIS,
    YAXIS,
    C_XAXIS,
    C_YAXIS,
    DPAD_UP,
    DPAD_RIGHT,
    DPAD_LEFT,
    DPAD_DOWN,
    TOTAL_INPUTS
};

// Pin definitions
const uint8_t LED_PIN = LED_BUILTIN;
const uint8_t CONTROLLER_DATA_PIN = 3;
const uint8_t CONSOLE_DATA_PIN = 5;

// according to 'Yet Another Gamecube Documentation.htm', min/max values for
// axis
const uint8_t MIN_AXIS_VAL = 32;
const uint8_t MAX_AXIS_VAL = 234;
const uint8_t AVG_AXIS_VAL = 127;

// if any axis (analog stick, c-stick, and L and R axes) changes by a difference
// below, do not record it
const uint8_t ALLOWABLE_AXIS_DRIFT = 10;

#endif // GCTRAIN_CONSTANTS_HPP_