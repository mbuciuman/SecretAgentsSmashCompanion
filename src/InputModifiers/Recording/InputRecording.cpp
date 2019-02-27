#include "InputRecording.hpp"

InputRecording::InputRecording()
    : initialData(Gamecube_Data_t()), previousData(Gamecube_Data_t()),
      currentData(Gamecube_Data_t()), previousTime(0), recording(false),
      inputDiffStore() {}

void InputRecording::startRecording(Gamecube_Data_t initialData) {
#ifdef DEBUG
    Serial.print(F("Starting recording"));
#endif
    inputDiffStore.reset();
    this->initialData = initialData;
    this->previousData = initialData;
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
        this->currentData = currentData;
        if (!currentDataEqualsPrevious()) {
#ifdef DEBUG
            Serial.println(F("PRINTING PREVIOUS REPORT"));
            printReport(previousData.report);
            Serial.println(F("PRINTING CURRENT REPORT"));
            printReport(currentData.report);
            Serial.println(F("Current data does not equal previous"));
#endif
            createNewDiff();
        }
        timeElapsed = millis() - previousTime;
    }
}

bool InputRecording::currentDataEqualsPrevious() {
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

void InputRecording::createNewDiff() {
    if (!inputDiffStore.canStoreDiff()) {
#ifdef DEBUG
        Serial.println(F("Reached max storage value! Stopping recording!"));
#endif
        return;
    }
    uint16_t timeDiff = timeElapsed;
    inputDiffStore.storeDiff(timeDiff, previousData.report, currentData.report);
    previousData = currentData;
    previousTime = millis();
}

#ifdef DEBUG
void InputRecording::printReport(Gamecube_Report_t &report) {
    // Prints the raw data from the controller
    Serial.println();
    Serial.println(F("Printing Gamecube controller report:"));
    Serial.print(F("Start:\t"));
    Serial.println(report.start);

    Serial.print(F("Y:\t"));
    Serial.println(report.y);

    Serial.print(F("X:\t"));
    Serial.println(report.x);

    Serial.print(F("B:\t"));
    Serial.println(report.b);

    Serial.print(F("A:\t"));
    Serial.println(report.a);

    Serial.print(F("L:\t"));
    Serial.println(report.l);
    Serial.print(F("R:\t"));
    Serial.println(report.r);
    Serial.print(F("Z:\t"));
    Serial.println(report.z);

    Serial.print(F("Dup:\t"));
    Serial.println(report.dup);
    Serial.print(F("Ddown:\t"));
    Serial.println(report.ddown);
    Serial.print(F("Dright:\t"));
    Serial.println(report.dright);
    Serial.print(F("Dleft:\t"));
    Serial.println(report.dleft);

    Serial.print(F("xAxis:\t"));
    Serial.println(report.xAxis, DEC);
    Serial.print(F("yAxis:\t"));
    Serial.println(report.yAxis, DEC);

    Serial.print(F("cxAxis:\t"));
    Serial.println(report.cxAxis, DEC);
    Serial.print(F("cyAxis:\t"));
    Serial.println(report.cyAxis, DEC);

    Serial.print(F("L:\t"));
    Serial.println(report.left, DEC);
    Serial.print(F("R:\t"));
    Serial.println(report.right, DEC);
    Serial.println();
}
#endif

InputDiffStore &InputRecording::getInputDiffStore() { return inputDiffStore; }

void InputRecording::cleanUp() {
    recording = false;
    inputDiffStore.storeLastTime(timeElapsed);
}