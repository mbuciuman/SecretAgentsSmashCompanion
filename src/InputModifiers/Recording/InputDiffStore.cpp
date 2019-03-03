#include "InputDiffStore.hpp"

InputDiffStore::InputDiffStore() : inputDiffs{}, totalDiffs(0) {}

void InputDiffStore::initialize(Gamecube_Data_t &initialData) {
    Gamecube_Data_t *dataPtr = &initialData;
    memcpy(&this->initialData, dataPtr, sizeof(this->initialData));
}

bool InputDiffStore::canStoreDiff() { return totalDiffs < MAX_STORE_SIZE; }

void InputDiffStore::storeDiff(uint16_t timeDiff,
                               Gamecube_Report_t &firstReport,
                               Gamecube_Report_t &secondReport) {
    inputDiffs[totalDiffs].initialize(timeDiff, firstReport, secondReport);
    totalDiffs++;
}

void InputDiffStore::storeLastTime(uint16_t lastTime) {
    this->lastTime = lastTime;
}

InputDiff &InputDiffStore::getDiff(int index) { return inputDiffs[index]; }

uint8_t InputDiffStore::getTotalDiffs() { return totalDiffs; }

uint16_t InputDiffStore::getLastTime() { return lastTime; }

Gamecube_Data_t InputDiffStore::getInitialData() {
    Gamecube_Data_t copy;
    Gamecube_Data_t *dataPtr = &initialData;
    memcpy(&copy, dataPtr, sizeof(copy));
    return copy;
}

void InputDiffStore::reset() {
    // totalDiffs is also used as the index of the latest stored diff
    totalDiffs = 0;
}