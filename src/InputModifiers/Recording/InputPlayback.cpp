#include "InputPlayback.hpp"

InputPlayback::InputPlayback(InputDiffStore &inputDiffStore)
    : initialData(Gamecube_Data_t()), playingBack(false), timeElapsed(0),
      currInputDiff(0), inputDiffStore(inputDiffStore) {}

void InputPlayback::initialize(Gamecube_Data_t &initialData) {
    this->initialData = initialData;
    timeElapsed = 0;
    startTime = millis();
    currInputDiff = 0;
    playingBack = true;
}

void InputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("ip_mi"));
#endif
    if (!playingBack) {
#ifdef DEBUG
        Serial.println(F("Initializing"));
#endif
        initialize(dataToModify);
    } else if (nextDiffExists()) {
#ifdef DEBUG
        Serial.println(F("Next diff exists!"));
#endif
        if (canApplyNextDiff()) {
#ifdef DEBUG
            Serial.println(F("Applying next diff!"));
#endif
            applyNextDiff(dataToModify);
            startTime = millis();
        }
        timeElapsed = (uint16_t)(millis() - startTime);
#ifdef DEBUG
        Serial.println(timeElapsed);
#endif
    } else if (timeElapsed < inputDiffStore.getLastTime()) {
#ifdef DEBUG
        Serial.println("Waiting for last time");
#endif
        timeElapsed = (uint16_t)(millis() - startTime);
    } else {
#ifdef DEBUG
        Serial.println(F("Restarting playback"));
#endif
        playingBack = false;
    }
}

bool InputPlayback::nextDiffExists() {
    return currInputDiff < inputDiffStore.getTotalDiffs() - 1;
}

bool InputPlayback::canApplyNextDiff() {
    return timeElapsed >
           inputDiffStore.getDiff(currInputDiff + 1).getTimeDiff();
}

void InputPlayback::applyNextDiff(Gamecube_Data_t &dataToModify) {
    inputDiffStore.getDiff(currInputDiff).applyTo(dataToModify);
    InputDiff nextDiff = inputDiffStore.getDiff(currInputDiff + 1);
    currInputDiff++;
}

void InputPlayback::cleanUp() { playingBack = false; }