#include "InputPlayback.hpp"

/**
 * @brief Construct a new Input Playback:: Input Playback object. Requires a
 * reference to an InputDiffStore.
 *
 * @param inputDiffStore
 */
InputPlayback::InputPlayback(InputDiffStore &inputDiffStore)
    : currentData(Gamecube_Data_t()), playingBack(false), timeElapsed(0),
      startTime(0), currInputDiffIndex(0), inputDiffStore(inputDiffStore) {}

/**
 * @brief Starts playback by initializing (or re-initializing) all variables.
 * Also called when restarting playback.
 *
 */
void InputPlayback::startPlayback() {
    currentData = inputDiffStore.getInitialData();
    timeElapsed = 0;
    startTime = millis();
    currInputDiffIndex = 0;
    playingBack = true;
}

/**
 * @brief Modifier method for input playback.
 * This is the main logic flow for handling playback.
 *
 * First checks to see if the playback flag is false and initializes all vars
 * for starting playback. Otherwise, we enter the logic for playing back.
 *
 * The main concept for this method is that this class has a 'currentData'
 * representing the input as it was recorded. The given 'dataToModify' is
 * continuously overridden with the 'currentData' values during playback.
 *
 * Once all diffs have been applied to 'currentData', then we just have to wait
 * for the time between the last input diff and when the recording stopped.
 *
 * @param dataToModify
 */
void InputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {
#ifdef DEBUG
    Serial.println(F("ip_mi"));
#endif
    timeElapsed = (uint16_t)(millis() - startTime);
    if (!playingBack) {
#ifdef DEBUG
        Serial.println(F("Initializing"));
#endif
        startPlayback();
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

/**
 * @brief Checks to see if there is another diff remaining.
 */
bool InputPlayback::nextDiffExists() {
    return currInputDiffIndex < inputDiffStore.getTotalDiffs();
}

/**
 * @brief Checks to see if enough time has elapsed before the next diff
 * should be applied.
 */
bool InputPlayback::canApplyNextDiff() {
    return timeElapsed >
           inputDiffStore.getDiff(currInputDiffIndex).getTimeDiff();
}

/**
 * @brief Applies the next diff to the 'currentData' var representing
 * the recorded input
 */
void InputPlayback::applyNextDiff() {
    inputDiffStore.getDiff(currInputDiffIndex).applyTo(currentData);
    currInputDiffIndex++;
}

/**
 * @brief Modifies the passed data with each input in the recorded data
 */
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

/**
 * @brief Stops playback as clean up
 */
void InputPlayback::cleanUp() { playingBack = false; }