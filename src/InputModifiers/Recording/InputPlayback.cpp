#include "InputPlayback.hpp"

InputPlayback::InputPlayback(InputDiffStore &inputDiffStore)
    : currentData(Gamecube_Data_t()), playingBack(false), timeElapsed(0),
      startTime(0), currInputDiffIndex(0), inputDiffStore(inputDiffStore) {}

void InputPlayback::initialize() {
    currentData = inputDiffStore.getInitialData();
    timeElapsed = 0;
    startTime = millis();
    currInputDiffIndex = 0;
    playingBack = true;
}

void InputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("ip_mi"));
#endif
    timeElapsed = (uint16_t)(millis() - startTime);
    if (!playingBack) {
#ifdef DEBUG
        Serial.println(F("Initializing"));
#endif
        initialize();
    } else if (nextDiffExists()) {
#ifdef DEBUG
        Serial.println(F("Next diff exists!"));
#endif
        if (canApplyNextDiff()) {
#ifdef DEBUG
            Serial.println(F("Applying next diff!"));
#endif
            applyNextDiff();
            startTime = millis();
        }
        modifyWithCurrentData(dataToModify);
#ifdef DEBUG
        Serial.println(timeElapsed);
#endif
    } else if (timeElapsed < inputDiffStore.getLastTime()) {
#ifdef DEBUG
        Serial.println("Waiting for last time");
#endif
        modifyWithCurrentData(dataToModify);
    } else {
#ifdef DEBUG
        Serial.println(F("Restarting playback"));
#endif
        playingBack = false;
    }
}

bool InputPlayback::nextDiffExists() {
    return currInputDiffIndex < inputDiffStore.getTotalDiffs();
}

bool InputPlayback::canApplyNextDiff() {
    return timeElapsed >
           inputDiffStore.getDiff(currInputDiffIndex).getTimeDiff();
}

void InputPlayback::applyNextDiff() {
    // apply next diff to current data
    inputDiffStore.getDiff(currInputDiffIndex).applyTo(currentData);
    currInputDiffIndex++;
}

void InputPlayback::modifyWithCurrentData(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("PRINTING CURRENT REPORT"));
    PrintReport::printReport(dataToModify.report);
#endif
    // store dpad inputs, then overwrite copied dpad inputs to allow them to
    // pass through
    uint8_t dpadLeft = dataToModify.report.dleft;
    uint8_t dpadUp = dataToModify.report.dup;
    uint8_t dpadRight = dataToModify.report.dright;
    uint8_t dpadDown = dataToModify.report.ddown;

    Gamecube_Data_t *dataPtr = &currentData;
    memcpy(&dataToModify, dataPtr, sizeof(dataToModify));

    dataToModify.report.dleft = dpadLeft;
    dataToModify.report.dup = dpadUp;
    dataToModify.report.dright = dpadRight;
    dataToModify.report.ddown = dpadDown;
#ifdef DEBUG
    Serial.println(F("PRINTING MODIFIED REPORT"));
    PrintReport::printReport(dataToModify.report);
#endif
}

void InputPlayback::cleanUp() { playingBack = false; }