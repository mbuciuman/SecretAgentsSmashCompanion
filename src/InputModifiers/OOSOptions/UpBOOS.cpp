#include "UpBOOS.hpp"

UpBOOS::UpBOOS() : nextState(State::SHIELD) {}

void UpBOOS::modifyInput(Gamecube_Data_t &dataToModify) {
    switch (nextState) {
    case State::SHIELD:
        dataToModify.report.left = MAX_AXIS_VAL;
        dataToModify.report.l = true;
        if (dataToModify.status.rumble) {
            nextState = State::UP_B;
        }
        break;
    case State::UP_B:
        dataToModify.report.xAxis = AVG_AXIS_VAL;
        dataToModify.report.yAxis = MAX_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::SHIELD;
        break;
    }
}

void UpBOOS::cleanUp() { nextState = State::SHIELD; }