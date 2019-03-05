/**
 * @file SecretAgentsSmashCompanion.cpp
 * @author Michael Buciuman-Coman (mbuciuma@gmail.com)
 * @brief Main logic for microcontroller. Recommend checking InputHandler.cpp
 * for majority of logic. All vars stored as statically-allocated data.
 * @version 1.0
 *
 */
#include "Constants.hpp"
#include "InputHandler.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <stdlib.h>
#include <time.h>

// Declare a Gamecube Controller
static CGamecubeController gcController(CONTROLLER_DATA_PIN);

// Declare Gamecube Console
static CGamecubeConsole gcConsole(CONSOLE_DATA_PIN);

// Declare Input Handler
static InputHandler inputHandler = InputHandler();

void setup() {
    // seed random number generator
    srand(time(NULL));

    // Set up debug led
    pinMode(LED_BUILTIN, OUTPUT);

#ifdef DEBUG
    // Start debug serial
    Serial.begin(115200);
#endif
}

void loop() {
    // Try to read the controller data
    if (gcController.read()) {

        // Print Controller information
        auto data = gcController.getData();

        // Process input using Input Handler
        inputHandler.processInput(data);
#ifdef WRITE
        // Write modified input to console
        if (!gcConsole.write(data)) {
#ifdef DEBUG
            Serial.println(F("ERRWRITE"));
#endif
            delay(ERR_DELAY);
        }
#endif
    } else {
        // Add debounce if reading failed
#ifdef DEBUG
        Serial.println(F("ERREAD"));
#endif
        delay(ERR_DELAY);
    }
}