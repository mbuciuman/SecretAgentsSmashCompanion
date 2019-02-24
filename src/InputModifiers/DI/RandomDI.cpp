#include "RandomDI.hpp"

#include <stdlib.h>
#include <time.h>

void RandomDI::modifyInput(Gamecube_Data_t &dataToModify) {
    Serial.println(F("rdi_mi"));
    int range = MAX_AXIS_VAL - MIN_AXIS_VAL;
    // determine random axis to set to max value
    bool useMaxForXAxis = rand() % 2 == 0;
    // set x and y axis to random value between min and max axis values
    dataToModify.report.xAxis =
        useMaxForXAxis ? MAX_AXIS_VAL : rand() % range + MIN_AXIS_VAL;
    dataToModify.report.yAxis =
        useMaxForXAxis ? rand() % range + MIN_AXIS_VAL + 1 : MAX_AXIS_VAL;
}

void RandomDI::cleanUp() {
    // nothing to do
}