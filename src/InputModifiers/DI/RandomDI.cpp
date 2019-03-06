#include "RandomDI.hpp"

RandomDI::RandomDI() : storedXAxis(AVG_AXIS_VAL), storedYAxis(AVG_AXIS_VAL) {}

void RandomDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("rdi_mi"));
#endif
    dataToModify.report.xAxis = storedXAxis;
    dataToModify.report.yAxis = storedYAxis;
    if (waitRemaining()) {
        return;
    }
    setInRandomDirection(storedXAxis, storedYAxis);
}

void RandomDI::cleanUp() {
    // nothing to do
}