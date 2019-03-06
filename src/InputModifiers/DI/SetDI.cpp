#include "SetDI.hpp"

SetDI::SetDI()
    : nextState(State::DIR_UNSET), storedXAxis(AVG_AXIS_VAL),
      storedYAxis(AVG_AXIS_VAL) {}

void SetDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("sdi_mi"));
#endif
    switch (nextState) {
    case State::DIR_UNSET:
        // store the given directions
        storedXAxis = dataToModify.report.xAxis;
        storedYAxis = dataToModify.report.yAxis;
        nextState = State::DI;
        break;
    case State::DI:
        // set the controller's axis to the stored values
        dataToModify.report.xAxis = storedXAxis;
        dataToModify.report.yAxis = storedYAxis;
        break;
    }
}

void SetDI::cleanUp() {
    // resets the state so axes can be re-stored when this modifier is
    // re-selected
    nextState = State::DIR_UNSET;
}