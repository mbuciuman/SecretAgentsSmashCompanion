#include "LeftRightSDI.hpp"

LeftRightSDI::LeftRightSDI() : movingRight(true), nextState(State::RIGHT) {}

void LeftRightSDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("lrsdi_mi"));
#endif
    switch (nextState) {
    case State::RIGHT:
        dataToModify.report.xAxis = MAX_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::NEUTRAL;
        break;
    case State::NEUTRAL:
        dataToModify.report.xAxis = AVG_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        if (movingRight) {
            nextState = State::RIGHT;
        } else {
            nextState = State::LEFT;
        }
        movingRight = !movingRight;
        break;
    case State::LEFT:
        dataToModify.report.xAxis = MIN_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::NEUTRAL;
        break;
    }
}

void LeftRightSDI::cleanUp() {
    // nothing to do
}