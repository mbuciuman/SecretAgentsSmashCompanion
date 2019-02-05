#include "MashJump.hpp"

MashJump::MashJump() { executingJump = false; }

void MashJump::inputEscapeOption(Gamecube_Data_t *dataToModify) {
    if (executingJump) {
        dataToModify->report.x = 0;
    } else {
        dataToModify->report.x = 1;
    }

    // toggle jump to input it every other frame
    executingJump = !executingJump;
}