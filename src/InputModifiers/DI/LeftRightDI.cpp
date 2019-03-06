#include "LeftRightDI.hpp"

LeftRightDI::LeftRightDI() : nextState(State::RIGHT) {}

void LeftRightDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("lrdi_mi"));
#endif
    switch (nextState) {
    case State::RIGHT:
        dataToModify.report.xAxis = MAX_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::LEFT;
        break;
    case State::LEFT:
        dataToModify.report.xAxis = MIN_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::RIGHT;
        break;
    }
}

void LeftRightDI::cleanUp() {
    // nothing to do
}