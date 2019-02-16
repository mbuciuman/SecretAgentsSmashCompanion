#include "MashJump.hpp"

MashJump::MashJump() : executingJump(false) {}

MashJump::~MashJump() {}

void MashJump::modifyInput(Gamecube_Data_t &dataToModify) {
    if (executingJump) {
        // toggle jump off if executing jump
        dataToModify.report.x = 0;
    } else {
        // toggle jump on if not executing jump
        dataToModify.report.x = 1;
    }

    // toggle var to input it every other frame
    executingJump = !executingJump;
}

void MashJump::cleanUp() {
    // nothing to do
}