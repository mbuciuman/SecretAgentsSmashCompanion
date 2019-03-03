#ifndef SASC_CONSTANTS_HPP_
#define SASC_CONSTANTS_HPP_

#include <Arduino.h>
#include <Nintendo.h>
#include <stdint.h>

// enum representing generic directions
enum class Direction : uint8_t { LEFT, UP, RIGHT, DOWN, NO_DIR };
// enum representing (useful) controller inputs
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

// maximum number of single input changes at a time (13 total possible):
// A, B, X, Y, Z, L, L (analog), R, R (analog), Analog stick X Axis, Analog
// stick Y Axis, C-Stick X Axis, C-Stick Y Axis
static const uint8_t MAX_SINGLE_INPUT_DIFFS = 13;

// maximum number of input diffs to be stored
// WARNING: when setting this, check the build's Data size to be smaller than
// the Microcontroller's A single button diff [SingleInputDiff] is 6 bytes, so
// each incrementing of the input diffs stored below is 6 bytes *
// MAX_SINGLE_INPUT_DIFFS
static const uint8_t MAX_STORE_SIZE = 20;

// frames to wait between inputs
static const uint8_t WAIT_FRAMES = 45;

// uncommenting enables heavy serial logging
// WARNING: should be paired with commenting WRITE below as serial logging slows
// down output to the point where it fails to write
//#define DEBUG

// uncommenting enables Gamecube writing
#define WRITE

#endif // SASC_CONSTANTS_HPP_