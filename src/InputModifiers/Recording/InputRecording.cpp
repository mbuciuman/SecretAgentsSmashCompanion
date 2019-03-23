#include "InputRecording.hpp"

/**
 * @brief Construct a new Input Recording:: Input Recording object
 */
InputRecording::InputRecording(InputChangeStore &inputChangeStore)
    : previousData(Gamecube_Data_t()), timeElapsed(0), previousTime(0),
      recording(false), inputChangeStore(inputChangeStore) {}

/**
 * @brief Starts the recording of inputs by initializing (or re-initializing)
 * all class vars. Also clears the Input Change Store.
 *
 * @param currentData The current controller input data
 */
void InputRecording::startRecording(const Gamecube_Data_t &currentData) {
#ifdef DEBUG
    Serial.print(F("Starting recording"));
#endif
    inputChangeStore.reset();
    inputChangeStore.initialize(currentData);
    previousData = currentData;
    timeElapsed = 0;
    previousTime = millis();
    recording = true;
}

/**
 * @brief Modifier method for input recording.
 *
 * First checks to see if the 'recording' flag is false and initializes all
 * class vars.
 *
 * The main logic checks to see if the previously stored input data differs from
 * the current controller input data, then stores the changes between the
 * input data into the Input Change store.
 *
 * @param currentData
 */
void InputRecording::modifyInput(Gamecube_Data_t &currentData) {
#ifdef DEBUG
    Serial.println(F("ir_mi"));
#endif
    if (!recording) {
        startRecording(currentData);
    } else {
        if (!currentDataEqualsPrevious(currentData)) {
#ifdef DEBUG
            Serial.println(F("PRINTING PREVIOUS REPORT"));
            printReport(previousData.report);
            Serial.println(F("PRINTING CURRENT REPORT"));
            printReport(currentData.report);
            Serial.println(F("Current data does not equal previous"));
#endif
            timeElapsed = millis() - previousTime;
            storeNewChange(currentData);
        }
    }
}

/**
 * @brief Checks to see if the current data differs from the previously stored
 * controller data.
 *
 * @param currentData current controller data
 */
bool InputRecording::currentDataEqualsPrevious(
    const Gamecube_Data_t &currentData) {
    Gamecube_Report_t previousReport = previousData.report;
    Gamecube_Report_t currentReport = currentData.report;
    int16_t leftDiff =
        abs((int16_t)currentReport.left - (int16_t)previousReport.left);
    int16_t rightDiff =
        abs((int16_t)currentReport.right - (int16_t)previousReport.right);
    int16_t xAxisDiff =
        abs((int16_t)currentReport.xAxis - (int16_t)previousReport.xAxis);
    int16_t yAxisDiff =
        abs((int16_t)currentReport.yAxis - (int16_t)previousReport.yAxis);
    int16_t cxAxisDiff =
        abs((int16_t)currentReport.cxAxis - (int16_t)previousReport.cxAxis);
    int16_t cyAxisDiff =
        abs((int16_t)currentReport.cyAxis - (int16_t)previousReport.cyAxis);

    return previousReport.a == currentReport.a &&
           previousReport.b == currentReport.b &&
           previousReport.x == currentReport.x &&
           previousReport.y == currentReport.y &&
           previousReport.z == currentReport.z &&
           previousReport.l == currentReport.l &&
           leftDiff < ALLOWABLE_AXIS_DRIFT &&
           previousReport.r == currentReport.r &&
           rightDiff < ALLOWABLE_AXIS_DRIFT &&
           xAxisDiff < ALLOWABLE_AXIS_DRIFT &&
           yAxisDiff < ALLOWABLE_AXIS_DRIFT &&
           cxAxisDiff < ALLOWABLE_AXIS_DRIFT &&
           cyAxisDiff < ALLOWABLE_AXIS_DRIFT;
}

/**
 * @brief Creates and stores a new Input Change in the Input Change store.
 *
 * @param currentData current controller data
 */
void InputRecording::storeNewChange(const Gamecube_Data_t &currentData) {
    if (!inputChangeStore.canStoreChange()) {
#ifdef DEBUG
        Serial.println(F("Reached max storage value! Stopping recording!"));
#endif
        return;
    }
    inputChangeStore.storeChange(timeElapsed, previousData.report,
                                 currentData.report);
    previousData = currentData;
    previousTime = millis();
}

/**
 * @brief Clean up method which stops recording and stores the time between the
 * last input change and when this class was cleaned up.
 */
void InputRecording::cleanUp() {
    recording = false;
    inputChangeStore.storeLastTime(millis() - previousTime);
}