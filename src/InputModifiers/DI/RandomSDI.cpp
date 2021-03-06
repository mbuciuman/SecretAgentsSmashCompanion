#include "RandomSDI.hpp"

RandomSDI::RandomSDI()
    : nextState(State::NEUTRAL), storedXAxis(AVG_AXIS_VAL),
      storedYAxis(AVG_AXIS_VAL) {}

void RandomSDI::modifyInput(Gamecube_Data_t &dataToModify) {
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
        setInRandomDirection(storedXAxis, storedYAxis);
        nextState = State::NEUTRAL;
        break;
    }
}

void RandomSDI::cleanUp() {
    // nothing to do
}