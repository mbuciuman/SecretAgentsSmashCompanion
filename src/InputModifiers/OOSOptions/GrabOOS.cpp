#include "GrabOOS.hpp"

GrabOOS::GrabOOS() : nextState(State::SHIELD) {}

void GrabOOS::modifyInput(Gamecube_Data_t &dataToModify) {
    switch (nextState) {
    case State::SHIELD:
        dataToModify.report.left = MAX_AXIS_VAL;
        dataToModify.report.l = true;
        if (dataToModify.status.rumble) {
            nextState = State::GRAB;
        }
        break;
    case State::GRAB:
        dataToModify.report.z = true;
        if (waitRemaining()) {
            return;
        }
        nextState = State::SHIELD;
        break;
    }
}

void GrabOOS::cleanUp() { nextState = State::SHIELD; }