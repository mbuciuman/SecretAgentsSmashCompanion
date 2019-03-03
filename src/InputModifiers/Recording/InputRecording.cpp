#include "InputRecording.hpp"

InputRecording::InputRecording()
    : previousData(Gamecube_Data_t()), timeElapsed(0), previousTime(0),
      recording(false), inputDiffStore() {}

void InputRecording::startRecording(Gamecube_Data_t &currentData) {
#ifdef DEBUG
    Serial.print(F("Starting recording"));
#endif
    inputDiffStore.reset();
    inputDiffStore.initialize(currentData);
    Gamecube_Data_t *dataPtr = &currentData;
    memcpy(&previousData, dataPtr, sizeof(previousData));
    timeElapsed = 0;
    previousTime = millis();
    recording = true;
}

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
            PrintReport::printReport(previousData.report);
            Serial.println(F("PRINTING CURRENT REPORT"));
            PrintReport::printReport(currentData.report);
            Serial.println(F("Current data does not equal previous"));
#endif
            timeElapsed = millis() - previousTime;
            createNewDiff(currentData);
        }
    }
}

bool InputRecording::currentDataEqualsPrevious(Gamecube_Data_t &currentData) {
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

void InputRecording::createNewDiff(Gamecube_Data_t &currentData) {
    if (!inputDiffStore.canStoreDiff()) {
#ifdef DEBUG
        Serial.println(F("Reached max storage value! Stopping recording!"));
#endif
        return;
    }
    inputDiffStore.storeDiff(timeElapsed, previousData.report,
                             currentData.report);
    Gamecube_Data_t *dataPtr = &currentData;
    memcpy(&previousData, dataPtr, sizeof(previousData));
    previousTime = millis();
}

InputDiffStore &InputRecording::getInputDiffStore() { return inputDiffStore; }

void InputRecording::cleanUp() {
    recording = false;
    inputDiffStore.storeLastTime(millis() - previousTime);
}