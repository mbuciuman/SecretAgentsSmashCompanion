#include "MashAirdodge.hpp"

#include <stdlib.h>
#include <time.h>

MashAirdodge::MashAirdodge() { executingAirdodge = false; }

void MashAirdodge::modifyInput(Gamecube_Data_t *dataToModify) {
    if (executingAirdodge) {
        // toggle airdodge off if executing airdodge
        dataToModify->report.l = 0;
        dataToModify->report.left = MIN_AXIS_VAL;
        dataToModify->report.xAxis = AVG_AXIS_VAL;
        dataToModify->report.yAxis = AVG_AXIS_VAL;
    } else {
        srand(time(NULL));
        int range = MAX_AXIS_VAL - MIN_AXIS_VAL;
        // toggle airdodge on if not executing airdodge
        dataToModify->report.l = 1;
        dataToModify->report.left = MAX_AXIS_VAL;
        // set x and y axis to random value between min and max axis values
        dataToModify->report.xAxis = rand() % range + MIN_AXIS_VAL + 1;
        dataToModify->report.yAxis = rand() % range + MIN_AXIS_VAL + 1;
    }

    // toggle var to input it every other frame
    executingAirdodge = !executingAirdodge;
}

void MashAirdodge::cleanUp() {
    // nothing to do
}