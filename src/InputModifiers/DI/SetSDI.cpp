#include "SetSDI.hpp"

SetSDI::SetSDI()
    : nextState(State::DIR_UNSET), storedXAxis(AVG_AXIS_VAL),
      storedYAxis(AVG_AXIS_VAL) {}

void SetSDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println("ssdi_mi");
#endif
    switch (nextState) {
    case State::DIR_UNSET:
        // store the given axis values
        storedXAxis = dataToModify.report.xAxis;
        storedYAxis = dataToModify.report.yAxis;
        nextState = State::NEUTRAL;
        break;
    case State::NEUTRAL:
        // return the axes to neutral
        dataToModify.report.xAxis = AVG_AXIS_VAL;
        dataToModify.report.yAxis = AVG_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::DI;
        break;
    case State::DI:
        // set the controller's axis to the stored values
        dataToModify.report.xAxis = storedXAxis;
        dataToModify.report.yAxis = storedYAxis;
        if (waitRemaining()) {
            return;
        }
        nextState = State::DI;
        break;
    }
}

void SetSDI::cleanUp() {
    // resets the state so axes can be re-stored when this modifier is
    // re-selected
    nextState = State::DIR_UNSET;
}