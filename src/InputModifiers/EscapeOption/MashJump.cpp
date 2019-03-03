#include "MashJump.hpp"

MashJump::MashJump() : nextState(State::NEUTRAL) {}

void MashJump::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("mj_mi"));
#endif
    switch (nextState) {
    case State::NEUTRAL:
        dataToModify.report.x = 0;
        if (waitRemaining()) {
            return;
        }
        nextState = State::JUMP;
        break;
    case State::JUMP:
        dataToModify.report.x = 1;
        if (waitRemaining()) {
            return;
        }
        nextState = State::NEUTRAL;
    }
}

void MashJump::cleanUp() {
    // nothing to do
}