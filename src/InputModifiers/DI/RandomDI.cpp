#include "RandomDI.hpp"

#include <stdlib.h>
#include <time.h>

RandomDI::RandomDI()
    : nextState(State::NEUTRAL), storedXAxis(MAX_AXIS_VAL),
      storedYAxis(MAX_AXIS_VAL) {}

void RandomDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("rdi_mi"));
#endif
    switch (nextState) {
    case State::NEUTRAL:
        dataToModify.report.xAxis = AVG_AXIS_VAL;
        dataToModify.report.yAxis = AVG_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::DI;
        break;
    case State::DI:
        dataToModify.report.xAxis = storedXAxis;
        dataToModify.report.yAxis = storedYAxis;
        if (waitRemaining()) {
            return;
        }

        // determine random axis to set min/max value
        bool useXAxis = (rand() % 2) == 0;
        // randomly choose whether to set previous axis to min or max value
        bool useMaxVal = (rand() % 2) == 0;

        // set the other axis to a random value
        if (useXAxis) {
            storedXAxis = useMaxVal ? MAX_AXIS_VAL : MIN_AXIS_VAL;
            storedYAxis =
                rand() % (MAX_AXIS_VAL - MIN_AXIS_VAL) + MIN_AXIS_VAL + 1;
        } else {
            storedXAxis =
                rand() % (MAX_AXIS_VAL - MIN_AXIS_VAL) + MIN_AXIS_VAL + 1;
            storedYAxis = useMaxVal ? MAX_AXIS_VAL : MIN_AXIS_VAL;
        }
        nextState = State::NEUTRAL;
        break;
    }
}

void RandomDI::cleanUp() {
    // nothing to do
}