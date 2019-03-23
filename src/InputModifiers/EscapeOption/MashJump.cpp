#include "MashJump.hpp"

MashJump::MashJump() : nextState(State::NEUTRAL) {}

void MashJump::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("mj_mi"));
#endif
    switch (nextState) {
    case State::NEUTRAL:
        dataToModify.report.x = false;
        if (waitRemaining()) {
            return;
        }
        nextState = State::JUMP;
        break;
    case State::JUMP:
        dataToModify.report.x = true;
        if (waitRemaining()) {
            return;
        }
        nextState = State::NEUTRAL;
    }
}

void MashJump::cleanUp() {
    // nothing to do
}