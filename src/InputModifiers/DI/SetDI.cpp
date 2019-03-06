#include "SetDI.hpp"

SetDI::SetDI()
    : nextState(State::DIR_UNSET), storedXAxis(AVG_AXIS_VAL),
      storedYAxis(AVG_AXIS_VAL) {}

void SetDI::modifyInput(Gamecube_Data_t &dataToModify) {
    switch (nextState) {
    case State::DIR_UNSET:
        storedXAxis = dataToModify.report.xAxis;
        storedYAxis = dataToModify.report.yAxis;
        nextState = State::DI;
        break;
    case State::DI:
        dataToModify.report.xAxis = storedXAxis;
        dataToModify.report.yAxis = storedYAxis;
        break;
    }
}

void SetDI::cleanUp() { nextState = State::DIR_UNSET; }