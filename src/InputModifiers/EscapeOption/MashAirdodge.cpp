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
        if (waitRemaining()) {
            return;
        }
        nextState = State::AIRDODGE;
        break;
    case State::AIRDODGE:
        dataToModify.report.l = 1;
        dataToModify.report.left = MAX_AXIS_VAL;
        if (waitRemaining()) {
            return;
        }
        nextState = State::NEUTRAL;
        break;
    }
}

void MashAirdodge::cleanUp() {
    // nothing to do
}