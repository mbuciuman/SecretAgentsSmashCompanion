#include "SetSDI.hpp"

SetSDI::SetSDI()
    : nextState(State::DIR_UNSET), storedXAxis(AVG_AXIS_VAL),
      storedYAxis(AVG_AXIS_VAL) {}

void SetSDI::modifyInput(Gamecube_Data_t &dataToModify) {
    switch (nextState) {
    case State::DIR_UNSET:
        storedXAxis = dataToModify.report.xAxis;
        storedYAxis = dataToModify.report.yAxis;
        nextState = State::NEUTRAL;
        break;
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
        nextState = State::DI;
        break;
    }
}

void SetSDI::cleanUp() { nextState = State::DIR_UNSET; }