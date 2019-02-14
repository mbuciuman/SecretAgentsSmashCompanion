#include "InputModifier.hpp"
#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <iterator.h>
#include <linked_list.h>

// DI imports
#include "DI/LeftRightDI.hpp"
#include "DI/NoDI.hpp"
#include "DI/RandomDI.hpp"

// EscapeOption imports
#include "EscapeOption/MashAirdodge.hpp"
#include "EscapeOption/MashJump.hpp"

// Input Recording imports
#include "Recording/InputRecording.hpp"
#include "Recording/NoInputRecording.hpp"

// Input Playback imports
#include "Recording/InputPlayback.hpp"
#include "Recording/NoInputPlayback.hpp"

// Define a Gamecube Controller
CGamecubeController GamecubeController(CONTROLLER_DATA_PIN);

// Define Gamecube Console
CGamecubeConsole GamecubeConsole(CONSOLE_DATA_PIN);

// DI vars
LinkedList<InputModifier> *allDI;
Iterator<InputModifier> *itDI;

// Escape Option vars
LinkedList<InputModifier> *allEscapeOptions;
Iterator<InputModifier> *itEscapeOption;

// Input Playback vars
LinkedList<InputModifier> *inputPlaybackOptions;
Iterator<InputModifier> *itInputPlayback;

// Input Recording vars
LinkedList<InputModifier> *inputRecordingOptions;
Iterator<InputModifier> *itInputRecording;

InputModifier *activeInputModifier;

// Directional button states
bool upPressed = false;
bool rightPressed = false;
bool downPressed = false;
bool leftPressed = false;

void checkInputChange(uint8_t input, bool *dirPressed,
                      LinkedList<InputModifier> *modifiers,
                      Iterator<InputModifier> *it) {
    if (input == 1) {
        *dirPressed = true;
    } else if (*dirPressed) {
        activeInputModifier->cleanUp();
        if (modifiers->contains(activeInputModifier)) {
            if (!it->moveNext()) {
                it->reset();
            }
        } else {
            it->reset();
        }
        activeInputModifier = it->current();
        *dirPressed = false;
    }
}

void detectInputChanges() {
    Gamecube_Report_t report = GamecubeController.getData().report;
    checkInputChange(report.dup, &upPressed, inputPlaybackOptions,
                     itInputPlayback);
    checkInputChange(report.dright, &rightPressed, allEscapeOptions,
                     itEscapeOption);
    checkInputChange(report.ddown, &downPressed, inputRecordingOptions,
                     itInputRecording);
    checkInputChange(report.dleft, &leftPressed, allDI, itDI);
}

void setup() {
    allDI = new LinkedList<InputModifier>();
    allDI->add(new NoDI());
    allDI->add(new LeftRightDI());
    allDI->add(new RandomDI());
    itDI = allDI->it();

    allEscapeOptions = new LinkedList<InputModifier>();
    allEscapeOptions->add(new MashJump());
    allEscapeOptions->add(new MashAirdodge());
    itEscapeOption = allEscapeOptions->it();

    inputRecordingOptions = new LinkedList<InputModifier>();
    inputRecordingOptions->add(new NoInputRecording());
    inputRecordingOptions->add(new InputRecording());

    inputPlaybackOptions = new LinkedList<InputModifier>();
    inputPlaybackOptions->add(new NoInputPlayback());
    inputPlaybackOptions->add(new InputPlayback());

    // Set up default starting modifier
    activeInputModifier = itDI->current();

    // Set up debug led
    pinMode(PIN_LED, OUTPUT);

    // Start debug serial
    Serial.begin(115200);
}

void loop() {
    // Try to read the controller data
    if (GamecubeController.read()) {
        detectInputChanges();
        // Mirror the controller data to the console
        if (!GamecubeConsole.write(GamecubeController)) {
            Serial.println(F("Error writing Gamecube controller."));
            digitalWrite(PIN_LED, HIGH);
            delay(1000);
        }
    } else {
        Serial.println(F("Error reading Gamecube controller."));
        digitalWrite(PIN_LED, HIGH);
        delay(1000);
    }
    digitalWrite(PIN_LED, LOW);
}
