#include "LeftRightSDI.hpp"

LeftRightSDI::LeftRightSDI()
    : movingRight(true), nextDirection(Direction::LEFT) {}

void LeftRightSDI::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("lrsdi_mi"));
#endif
    switch (nextDirection) {
    case Direction::NO_DIR:
        dataToModify.report.xAxis = AVG_AXIS_VAL;
#ifdef DEBUG
        Serial.println(F("Moving in NODIR"));
#endif
        if (waitRemaining()) {
            return;
        }
        if (movingRight) {
            nextDirection = Direction::RIGHT;
        } else {
            nextDirection = Direction::LEFT;
        }
        movingRight = !movingRight;
        break;
    case Direction::RIGHT:
        dataToModify.report.xAxis = MAX_AXIS_VAL;
#ifdef DEBUG
        Serial.println(F("Moving RIGHT"));
#endif
        if (waitRemaining()) {
            return;
        }
        nextDirection = Direction::NO_DIR;
        break;
    case Direction::LEFT:
        dataToModify.report.xAxis = MIN_AXIS_VAL;
#ifdef DEBUG
        Serial.println(F("Moving LEFT"));
#endif
        if (waitRemaining()) {
            return;
        }
        nextDirection = Direction::NO_DIR;
        break;
    default:
        break;
    }
}

void LeftRightSDI::cleanUp() {
    // nothing to do
}