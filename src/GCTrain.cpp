#include "InputHandler.hpp"
#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

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

    // Start debug serial
    Serial.begin(115200);
}

#ifdef DEBUG
void print_gc_report(Gamecube_Report_t &gc_report,
                     Gamecube_Status_t &gc_status) {
    // Print device information
    Serial.print(F("Device: "));
    switch (gc_status.device) {
    case NINTENDO_DEVICE_GC_NONE:
        Serial.println(F("No Gamecube Controller found!"));
        break;
    case NINTENDO_DEVICE_GC_WIRED:
        Serial.println(F("Original Nintendo Gamecube Controller"));
        break;

    default:
        Serial.print(F("Unknown "));
        Serial.println(gc_status.device, HEX);
        break;
    }

    // Print rumble state
    Serial.print(F("Rumble "));
    if (gc_status.rumble)
        Serial.println(F("on"));
    else
        Serial.println(F("off"));

    // Prints the raw data from the controller
    Serial.println();
    Serial.println(F("Printing Gamecube controller report:"));
    Serial.print(F("Start:\t"));
    Serial.println(gc_report.start);

    Serial.print(F("Y:\t"));
    Serial.println(gc_report.y);

    Serial.print(F("X:\t"));
    Serial.println(gc_report.x);

    Serial.print(F("B:\t"));
    Serial.println(gc_report.b);

    Serial.print(F("A:\t"));
    Serial.println(gc_report.a);

    Serial.print(F("L:\t"));
    Serial.println(gc_report.l);
    Serial.print(F("R:\t"));
    Serial.println(gc_report.r);
    Serial.print(F("Z:\t"));
    Serial.println(gc_report.z);

    Serial.print(F("Dup:\t"));
    Serial.println(gc_report.dup);
    Serial.print(F("Ddown:\t"));
    Serial.println(gc_report.ddown);
    Serial.print(F("Dright:\t"));
    Serial.println(gc_report.dright);
    Serial.print(F("Dleft:\t"));
    Serial.println(gc_report.dleft);

    Serial.print(F("xAxis:\t"));
    Serial.println(gc_report.xAxis, DEC);
    Serial.print(F("yAxis:\t"));
    Serial.println(gc_report.yAxis, DEC);

    Serial.print(F("cxAxis:\t"));
    Serial.println(gc_report.cxAxis, DEC);
    Serial.print(F("cyAxis:\t"));
    Serial.println(gc_report.cyAxis, DEC);

    Serial.print(F("L:\t"));
    Serial.println(gc_report.left, DEC);
    Serial.print(F("R:\t"));
    Serial.println(gc_report.right, DEC);
    Serial.println();
}

void loop() {
    // Try to read the controller data
    if (gcController.read()) {
        // Print Controller information
        auto status = gcController.getStatus();
        auto report = gcController.getReport();
        print_gc_report(report, status);
        delay(100);
    } else {
        // Add debounce if reading failed
        Serial.println(F("Error reading Gamecube controller."));
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
    }
    digitalWrite(LED_PIN, LOW);
}
#endif

#ifndef DEBUG

void loop() {
    // Try to read the controller data
    if (gcController.read()) {
        // Print Controller information
        auto data = gcController.getData();
        inputHandler.processInput(data);
        delay(10);
    } else {
        // Add debounce if reading failed
        Serial.println(F("ERREAD"));
        digitalWrite(LED_PIN, HIGH);
        delay(10);
    }
    digitalWrite(LED_PIN, LOW);
}
#endif