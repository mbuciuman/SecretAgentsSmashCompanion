#include "NairOOS.hpp"

NairOOS::NairOOS() : nextState(State::SHIELD) {}

void NairOOS::modifyInput(Gamecube_Data_t &dataToModify) {
    switch (nextState) {
    case State::SHIELD:
        dataToModify.report.left = MAX_AXIS_VAL;
        dataToModify.report.l = true;
        if (dataToModify.status.rumble) {
            nextState = State::NAIR;
        }
        break;
    case State::NAIR:
        dataToModify.report.x = true;
        dataToModify.report.a = true;
        if (waitRemaining()) {
            return;
        }
        nextState = State::SHIELD;
    }
}

void NairOOS::cleanUp() { nextState = State::SHIELD; }