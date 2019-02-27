#include "InputHandler.hpp"
#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <stdlib.h>
#include <time.h>

// Declare a Gamecube Controller
CGamecubeController gcController(CONTROLLER_DATA_PIN);

// Declare Gamecube Console
CGamecubeConsole gcConsole(CONSOLE_DATA_PIN);

// Declare Input Handler
InputHandler inputHandler = InputHandler();

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
        inputHandler.processInput(data);
#ifdef WRITE
        if (!gcConsole.write(data)) {
#ifdef DEBUG
            Serial.println(F("ERRWRITE"));
#endif
            delay(100);
        }
#endif
    } else {
        // Add debounce if reading failed
#ifdef DEBUG
        Serial.println(F("ERREAD"));
        digitalWrite(LED_PIN, HIGH);
#endif
        delay(100);
    }
#ifdef DEBUG
    digitalWrite(LED_PIN, LOW);
#endif
}