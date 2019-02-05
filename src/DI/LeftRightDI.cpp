#include "LeftRightDI.hpp"

LeftRightDI::LeftRightDI()
{
    prevDirection = Direction::LEFT;
}

void LeftRightDI::inputDI(Gamecube_Data_t* dataToModify)
{
    if(prevDirection == Direction::LEFT) {
        dataToModify->report.xAxis = MAX_AXIS_VAL;
        prevDirection = Direction::RIGHT;
    } else if (prevDirection == Direction::RIGHT) {
        // according to 'Yet Another Gamecube Documentation.htm', min value for xAxis
        dataToModify->report.xAxis = MIN_AXIS_VAL;
        prevDirection = Direction::LEFT;
    }
}