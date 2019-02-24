#include "NoModifier.hpp"

NoModifier::NoModifier() {}

void NoModifier::modifyInput(Gamecube_Data_t &dataToModify) {
    Serial.println(F("NOMOD"));
    // nothing to do
}

void NoModifier::cleanUp() {
    // nothing to do
}