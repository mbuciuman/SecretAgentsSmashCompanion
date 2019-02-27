#include "NoModifier.hpp"

NoModifier::NoModifier() {}

void NoModifier::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("NOMOD"));
#endif
    // nothing to do
}

void NoModifier::cleanUp() {
    // nothing to do
}