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
#include "EscapeOption/NoEscapeOption.hpp"

// Define a Gamecube Controller
CGamecubeConsole GamecubeController(CONTROLLER_DATA_PIN);

// Define Gamecube Console
CGamecubeController GamecubeConsole(CONSOLE_DATA_PIN);

// Current DI setting
LinkedList<DI> *allDI;
Iterator<DI> *itDI;
DI *activeDI;

// Current escape option
/*
LinkedList<EscapeOption> allEscapeOptions;
EscapeOption *activeEscapeOption;
*/
void setup() {
    allDI = new LinkedList<DI>();
    allDI->add(new NoDI());
    allDI->add(new LeftRightDI());
    allDI->add(new RandomDI());
    itDI = allDI->it();
    activeDI = itDI->current();
}

void loop() {}