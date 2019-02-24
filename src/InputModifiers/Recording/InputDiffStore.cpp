#include "InputDiffStore.hpp"

InputDiffStore::InputDiffStore() : inputDiffs{}, totalDiffs(0) {}

bool InputDiffStore::canStoreDiff() { return totalDiffs < MAX_STORE_SIZE - 1; }

void InputDiffStore::storeDiff(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                               Gamecube_Report_t &secondReport) {
    inputDiffs[totalDiffs].initialize(timeDiff, firstReport, secondReport);
    totalDiffs++;
}

InputDiff &InputDiffStore::getDiff(int index) { return inputDiffs[index]; }

uint8_t InputDiffStore::getTotalDiffs() { return totalDiffs; }

void InputDiffStore::reset() {
    totalDiffs = 0; // resets the index at which the next diff will be stored
}