#include "UpSmashOOS.hpp"

UpSmashOOS::UpSmashOOS() : nextState(State::SHIELD) {}

void UpSmashOOS::modifyInput(Gamecube_Data_t &dataToModify) {
    switch (nextState) {
    case State::SHIELD:
        dataToModify.report.left = MAX_AXIS_VAL;
        dataToModify.report.l = true;
        if (dataToModify.status.rumble) {
            nextState = State::UP_SMASH;
        }
        break;
    case State::UP_SMASH:
        dataToModify.report.xAxis = AVG_AXIS_VAL;
        dataToModify.report.yAxis = MAX_AXIS_VAL;
        dataToModify.report.a = true;
        if (waitRemaining()) {
            return;
        }
        nextState = State::SHIELD;
        break;
    }
}

void UpSmashOOS::cleanUp() { nextState = State::SHIELD; }