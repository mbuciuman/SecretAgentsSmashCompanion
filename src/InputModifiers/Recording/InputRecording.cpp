#include "InputRecording.hpp"

InputRecording::InputRecording()
    : initialData(Gamecube_Data_t()), previousData(Gamecube_Data_t()),
      currentData(Gamecube_Data_t()), previousTime(0), recording(false),
      inputDiffs(new LinkedList<InputDiff>()) {}

InputRecording::~InputRecording() { delete inputDiffs; }

void InputRecording::startRecording(Gamecube_Data_t initialData) {
    this->initialData = initialData;
    previousTime = 0;
    recording = true;
}

void InputRecording::modifyInput(Gamecube_Data_t &currentData) {
    if (!recording) {
        startRecording(currentData);
    } else {
        this->currentData = currentData;
        if (!currentDataEqualsPrevious()) {
            createNewDiff();
        }
    }
}

bool InputRecording::currentDataEqualsPrevious() {
    Gamecube_Report_t previousReport = previousData.report;
    Gamecube_Report_t currentReport = currentData.report;
    return previousReport.a != currentReport.a &&
           previousReport.b != currentReport.b &&
           previousReport.x != currentReport.x &&
           previousReport.y != currentReport.y &&
           previousReport.z != currentReport.z &&
           previousReport.l != currentReport.l &&
           previousReport.left != currentReport.left &&
           previousReport.r != currentReport.r &&
           previousReport.right != currentReport.right &&
           previousReport.xAxis != currentReport.xAxis &&
           previousReport.yAxis != currentReport.yAxis &&
           previousReport.cxAxis != currentReport.cxAxis &&
           previousReport.cyAxis != currentReport.cyAxis;
}

void InputRecording::createNewDiff() {
    unsigned long currentTime = millis();
    unsigned long timeDiff = currentTime - previousTime;
    inputDiffs->add(
        new InputDiff(timeDiff, previousData.report, currentData.report));
    previousData = currentData;
    previousTime = currentTime;
}

LinkedList<InputDiff> *InputRecording::getInputDiffs() { return inputDiffs; }

void InputRecording::cleanUp() { recording = false; }