#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <iterator.h>
#include <linked_list.h>
#include "InputModifier.hpp"

// DI imports
#include "DI/LeftRightDI.hpp"
#include "DI/NoDI.hpp"
#include "DI/RandomDI.hpp"

// EscapeOption imports
#include "EscapeOption/MashJump.hpp"
#include "EscapeOption/MashAirdodge.hpp"
#include "EscapeOption/NoEscapeOption.hpp"

// Define a Gamecube Controller
CGamecubeController GamecubeController(CONTROLLER_DATA_PIN);

// Define Gamecube Console
CGamecubeConsole GamecubeConsole(CONSOLE_DATA_PIN);

// Current DI setting
LinkedList<InputModifier> *allDI;
Iterator<InputModifier> *itDI;
InputModifier *activeDI;

// Current escape option
LinkedList<InputModifier> *allEscapeOptions;
Iterator<InputModifier> *itEscapeOption;
InputModifier *activeEscapeOption;

void setup() {
    allDI = new LinkedList<InputModifier>();
    allDI->add(new NoDI());
    allDI->add(new LeftRightDI());
    allDI->add(new RandomDI());
    itDI = allDI->it();
    activeDI = itDI->current();

    allEscapeOptions = new LinkedList<InputModifier>();
    allEscapeOptions->add(new NoEscapeOption());
    allEscapeOptions->add(new MashJump());
    allEscapeOptions->add(new MashAirdodge());
    itEscapeOption = allEscapeOptions->it();
    activeEscapeOption = itEscapeOption->current();

    // Set up debug led
    pinMode(PIN_LED, OUTPUT);

    // Start debug serial
    Serial.begin(115200);
}

void loop() {
    // Try to read the controller data
    if (GamecubeController.read()) {
        // Mirror the controller data to the console
        if (!GamecubeConsole.write(GamecubeController))
        {
            Serial.println(F("Error writing Gamecube controller."));
            digitalWrite(PIN_LED, HIGH);
            delay(1000);
        }
    }
    else {
        Serial.println(F("Error reading Gamecube controller."));
        digitalWrite(PIN_LED, HIGH);
        delay(1000);
    }
    digitalWrite(PIN_LED, LOW);
}