#include "LeftRightDI.hpp"

LeftRightDI::LeftRightDI() { prevDirection = Direction::LEFT; }

void LeftRightDI::modifyInput(Gamecube_Data_t &dataToModify) {
    if (prevDirection == Direction::LEFT) {
        dataToModify.report.xAxis = MAX_AXIS_VAL;
        prevDirection = Direction::RIGHT;
    } else if (prevDirection == Direction::RIGHT) {
        dataToModify.report.xAxis = MIN_AXIS_VAL;
        prevDirection = Direction::LEFT;
    }
}

void LeftRightDI::cleanUp() {
    // nothing to do
}