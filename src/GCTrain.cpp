#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <iterator.h>
#include <linked_list.h>

// DI imports
#include "DI/DI.hpp"
#include "DI/LeftRightDI.hpp"
#include "DI/NoDI.hpp"
#include "DI/RandomDI.hpp"

// EscapeOption imports
#include "EscapeOption/EscapeOption.hpp"
#include "EscapeOption/MashJump.hpp"
#include "EscapeOption/MashAirdodge.hpp"
#include "EscapeOption/NoEscapeOption.hpp"

// Define a Gamecube Controller
CGamecubeController GamecubeController(CONTROLLER_DATA_PIN);

// Define Gamecube Console
CGamecubeConsole GamecubeConsole(CONSOLE_DATA_PIN);

// Current DI setting
LinkedList<DI> *allDI;
Iterator<DI> *itDI;
DI *activeDI;

// Current escape option
LinkedList<EscapeOption> *allEscapeOptions;
Iterator<EscapeOption> *itEscapeOption;
EscapeOption *activeEscapeOption;

void setup() {
    allDI = new LinkedList<DI>();
    allDI->add(new NoDI());
    allDI->add(new LeftRightDI());
    allDI->add(new RandomDI());
    itDI = allDI->it();
    activeDI = itDI->current();

    allEscapeOptions = new LinkedList<EscapeOption>();
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