#include "MashAirdodge.hpp"

#include <stdlib.h>
#include <time.h>

MashAirdodge::MashAirdodge()
    : nextState(State::NEUTRAL), storedXAxis(MAX_AXIS_VAL),
      storedYAxis(MAX_AXIS_VAL) {}

void MashAirdodge::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("ma_mi"));
#endif
    switch (nextState) {
    case State::NEUTRAL:
        dataToModify.report.l = 0;
        dataToModify.report.left = MIN_AXIS_VAL;
        dataToModify.report.xAxis = AVG_AXIS_VAL;
        dataToModify.report.yAxis = AVG_AXIS_VAL;
#ifdef DEBUG
        Serial.println(F("Inputting NEUTRAL"));
#endif
        if (waitRemaining()) {
            return;
        }
        nextState = State::AIRDODGE;
        break;
    case State::AIRDODGE:
        dataToModify.report.l = 1;
        dataToModify.report.left = MAX_AXIS_VAL;
        dataToModify.report.xAxis = storedXAxis;
        dataToModify.report.yAxis = storedYAxis;
#ifdef DEBUG
        Serial.println(F("Inputting AIRDODGE"));
#endif
        if (waitRemaining()) {
            return;
        }

        // determine random axis to set min/max value
        bool useXAxis = (rand() % 2) == 0;
        // randomly choose whether to set previous axis to min or max value
        bool useMaxVal = (rand() % 2) == 0;

        // set the other axis to a random value
        if (useXAxis) {
            storedXAxis = useMaxVal ? MAX_AXIS_VAL : MIN_AXIS_VAL;
            storedYAxis =
                rand() % (MAX_AXIS_VAL - MIN_AXIS_VAL) + MIN_AXIS_VAL + 1;
        } else {
            storedXAxis =
                rand() % (MAX_AXIS_VAL - MIN_AXIS_VAL) + MIN_AXIS_VAL + 1;
            storedYAxis = useMaxVal ? MAX_AXIS_VAL : MIN_AXIS_VAL;
        }
        nextState = State::NEUTRAL;
        break;
    }
}

void MashAirdodge::cleanUp() {
    // nothing to do
}