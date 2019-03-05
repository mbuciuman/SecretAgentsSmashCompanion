#include "InputChangeStore.hpp"

/**
 * @brief Construct a new Input Change Store:: Input Change Store object.
 *
 */
InputChangeStore::InputChangeStore() : inputChanges{}, totalChanges(0) {}

/**
 * @brief Initializes the store with an initial controller data.
 *
 * @param initialData reference to current controller data
 */
void InputChangeStore::initialize(Gamecube_Data_t &initialData) {
    this->initialData = initialData;
}

/**
 * @brief Checks to see if another Input Change can be stored.
 */
bool InputChangeStore::canStoreChange() {
    return totalChanges < MAX_STORE_SIZE;
}

/**
 * @brief Stores an Input Change with its time elapsed from the previously
 * stored input.
 *
 * @param timeDiff the time elapsed between the two given controller data
 * @param firstReport the first controller data
 * @param secondReport the second controller data
 */
void InputChangeStore::storeChange(uint16_t timeDiff,
                                   Gamecube_Report_t &firstReport,
                                   Gamecube_Report_t &secondReport) {
    inputChanges[totalChanges].initialize(timeDiff, firstReport, secondReport);
    totalChanges++;
}

/**
 * @brief Returns a reference to the Input Change stored at the given index.
 */
InputChange &InputChangeStore::getInputChange(int index) {
    return inputChanges[index];
}

/**
 * @brief Returns the number of total input changes stored.
 */
uint8_t InputChangeStore::getTotalChanges() { return totalChanges; }

/**
 * @brief Stores the time between the last-stored Input Change and the end of
 * recording.
 *
 * @param lastTime time in milliseconds
 */
void InputChangeStore::storeLastTime(uint16_t lastTime) {
    this->lastTime = lastTime;
}

/**
 * @brief Returns the time between the last-stored Input Change and the end of
 * recording.
 *
 * @return uint16_t time in milliseconds
 */
uint16_t InputChangeStore::getLastTime() { return lastTime; }

/**
 * @brief Returns the initial controller data.
 */
Gamecube_Data_t InputChangeStore::getInitialData() { return initialData; }

/**
 * @brief Resets the Input Change store to its pre-recording state.
 */
void InputChangeStore::reset() {
    // setting 'totalChanges' to 0 should be equivalent to re-starting recording
    totalChanges = 0;
}