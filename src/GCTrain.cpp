#include "InputHandler.hpp"
#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <iterator.h>
#include <linked_list.h>
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
    pinMode(PIN_LED, OUTPUT);

    // Start debug serial
    Serial.begin(115200);
}

void loop() {
    // Try to read the controller data
    if (gcController.read()) {

        // Copy the controller data and send it to the input handler for
        // processing
        Gamecube_Data_t gcData = gcController.getData();
        inputHandler.processInput(gcData);

        // Send the modified data to the console
        if (!gcConsole.write(gcData)) {
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
