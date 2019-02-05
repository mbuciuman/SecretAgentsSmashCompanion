#include "RandomDI.hpp"

#include <stdlib.h>
#include <time.h>

void RandomDI::inputDI(Gamecube_Data_t *dataToModify) {
    srand(time(NULL));
    int range = MAX_AXIS_VAL - MIN_AXIS_VAL;
    // set x and y axis to random value between min and max axis values
    dataToModify->report.xAxis = rand() % range + MIN_AXIS_VAL + 1;
    dataToModify->report.yAxis = rand() % range + MIN_AXIS_VAL + 1;
}