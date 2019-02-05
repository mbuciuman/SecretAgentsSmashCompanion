#include <Arduino.h>
#include <Nintendo.h>
#include "constants.hpp"

// DI imports
#include "DI/DI.hpp"
#include "DI/NoDI.hpp"
#include "DI/LeftRightDI.hpp"

// Define a Gamecube Controller
CGamecubeConsole GamecubeController(CONTROLLER_DATA_PIN);

// Define Gamecube Console
CGamecubeController GamecubeConsole(CONSOLE_DATA_PIN);

// Current DI setting
DI* activeDI;

// Current escape option
EscapeOption* activeEscapeOption;

void setup()
{
    activeDI = new NoDI;
}

void loop()
{
}