#include "constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>

// DI imports
#include "DI/DI.hpp"
#include "DI/LeftRightDI.hpp"
#include "DI/NoDI.hpp"

// EscapeOption imports
#include "EscapeOption/EscapeOption.hpp"
#include "EscapeOption/MashJump.hpp"
#include "EscapeOption/NoEscapeOption.hpp"

// Define a Gamecube Controller
CGamecubeConsole GamecubeController(CONTROLLER_DATA_PIN);

// Define Gamecube Console
CGamecubeController GamecubeConsole(CONSOLE_DATA_PIN);

// Current DI setting
DI *activeDI;

// Current escape option
EscapeOption *activeEscapeOption;

void setup() {
    activeDI = new NoDI;
    activeEscapeOption = new NoEscapeOption;
}

void loop() {}