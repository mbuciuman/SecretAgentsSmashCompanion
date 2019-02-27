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
static const uint8_t LED_PIN = LED_BUILTIN;
static const uint8_t CONTROLLER_DATA_PIN = 3;
static const uint8_t CONSOLE_DATA_PIN = 4;

// according to 'Yet Another Gamecube Documentation.htm', min/max values for
// axis
static const uint8_t MIN_AXIS_VAL = 32;
static const uint8_t MAX_AXIS_VAL = 234;
static const uint8_t AVG_AXIS_VAL = 127;

// if any axis (analog stick, c-stick, and L and R axes) changes by a difference
// below, do not record it
static const uint8_t ALLOWABLE_AXIS_DRIFT = 10;

// maximum number of consecutive input changes at a time (17 total possible)
static const uint8_t MAX_CONS_INPUTS = 8;

// maximum number of input diffs to be stored
static const uint8_t MAX_STORE_SIZE = 10;

// uncommenting enables heavy serial logging
//#define DEBUG

#endif // GCTRAIN_CONSTANTS_HPP_