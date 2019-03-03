#include "InputDiffStore.hpp"

/**
 * @brief Construct a new Input Diff Store:: Input Diff Store object.
 *
 */
InputDiffStore::InputDiffStore() : inputDiffs{}, totalDiffs(0) {}

/**
 * @brief Initializes the store with an initial controller data.
 *
 * @param initialData reference to current controller data
 */
void InputDiffStore::initialize(Gamecube_Data_t &initialData) {
    Gamecube_Data_t *dataPtr = &initialData;
    memcpy(&this->initialData, dataPtr, sizeof(this->initialData));
}

/**
 * @brief Checks to see if another input diff can be stored.
 */
bool InputDiffStore::canStoreDiff() { return totalDiffs < MAX_STORE_SIZE; }

/**
 * @brief Stores an input diff with its time elapsed from the previously stored
 * input.
 *
 * @param timeDiff the time elapsed between the two given controller data
 * @param firstReport the first controller data
 * @param secondReport the second controller data
 */
void InputDiffStore::storeDiff(uint16_t timeDiff,
                               Gamecube_Report_t &firstReport,
                               Gamecube_Report_t &secondReport) {
    inputDiffs[totalDiffs].initialize(timeDiff, firstReport, secondReport);
    totalDiffs++;
}

/**
 * @brief Returns a reference to the input diff stored at the given index.
 */
InputDiff &InputDiffStore::getDiff(int index) { return inputDiffs[index]; }

/**
 * @brief Returns the number of total diffs stored.
 */
uint8_t InputDiffStore::getTotalDiffs() { return totalDiffs; }

/**
 * @brief Stores the time between the last-stored input diff and the end of
 * recording.
 *
 * @param lastTime time in milliseconds
 */
void InputDiffStore::storeLastTime(uint16_t lastTime) {
    this->lastTime = lastTime;
}

/**
 * @brief Returns the time between the last-stored input diff and the end of
 * recording.
 *
 * @return uint16_t time in milliseconds
 */
uint16_t InputDiffStore::getLastTime() { return lastTime; }

/**
 * @brief Returns the initial controller data.
 */
Gamecube_Data_t InputDiffStore::getInitialData() {
    Gamecube_Data_t copy;
    Gamecube_Data_t *dataPtr = &initialData;
    memcpy(&copy, dataPtr, sizeof(copy));
    return copy;
}

/**
 * @brief Resets the input diff store to its pre-recording state.
 */
void InputDiffStore::reset() {
    // setting 'totalDiffs' to 0 should be equivalent to re-starting recording
    totalDiffs = 0;
}