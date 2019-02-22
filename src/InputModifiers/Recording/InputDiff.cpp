#include "InputDiff.hpp"

InputDiff::InputDiff(long timeDiff, Gamecube_Report_t &firstReport,
                     Gamecube_Report_t &secondReport)
    : timeDiff(timeDiff), singleDiffs(new LinkedList<SingleInputDiff>()) {
    initialize(firstReport, secondReport);
}

InputDiff::~InputDiff() { delete singleDiffs; }

void InputDiff::initialize(Gamecube_Report_t &firstReport,
                           Gamecube_Report_t &secondReport) {
    addDiffIfDifferent(firstReport.a, secondReport.a, ControllerInput::A);
    addDiffIfDifferent(firstReport.b, secondReport.b, ControllerInput::B);
    addDiffIfDifferent(firstReport.x, secondReport.x, ControllerInput::X);
    addDiffIfDifferent(firstReport.y, secondReport.y, ControllerInput::Y);
    addDiffIfDifferent(firstReport.z, secondReport.z, ControllerInput::Z);
    addDiffIfDifferent(firstReport.l, secondReport.l, ControllerInput::L);
    addDiffIfDifferent(firstReport.left, secondReport.left,
                       ControllerInput::L_ANALOG);
    addDiffIfDifferent(firstReport.r, secondReport.r, ControllerInput::R);
    addDiffIfDifferent(firstReport.right, secondReport.right,
                       ControllerInput::R_ANALOG);
    addDiffIfDifferent(firstReport.xAxis, secondReport.xAxis,
                       ControllerInput::XAXIS);
    addDiffIfDifferent(firstReport.yAxis, secondReport.yAxis,
                       ControllerInput::YAXIS);
    addDiffIfDifferent(firstReport.cxAxis, secondReport.cxAxis,
                       ControllerInput::C_XAXIS);
    addDiffIfDifferent(firstReport.cyAxis, secondReport.cyAxis,
                       ControllerInput::C_YAXIS);
}

void InputDiff::addDiffIfDifferent(uint8_t firstVal, uint8_t secondVal,
                                   ControllerInput input) {
    if (firstVal != secondVal) {
        int16_t diff = (int16_t)firstVal - (int16_t)secondVal;
        SingleInputDiff *singleInputDiff = new SingleInputDiff;
        singleInputDiff->input = input;
        singleInputDiff->valueDiff = diff;
        singleDiffs->add(singleInputDiff);
    }
}

unsigned long InputDiff::getTimeDiff() { return timeDiff; }

void InputDiff::applyDiff(Gamecube_Data_t &dataToModify) {
    Iterator<SingleInputDiff> *itSIDiff = singleDiffs->it();
    SingleInputDiff *singleDiff = itSIDiff->current();
    while (singleDiff != nullptr) {
        applySingleDiff(singleDiff, dataToModify);
        itSIDiff->moveNext();
        singleDiff = itSIDiff->current();
    }
}

void InputDiff::applySingleDiff(SingleInputDiff *singleDiff,
                                Gamecube_Data_t &dataToModify) {
    switch (singleDiff->input) {
    case ControllerInput::A:
        dataToModify.report.a += singleDiff->valueDiff;
        break;
    case ControllerInput::B:
        dataToModify.report.b += singleDiff->valueDiff;
        break;
    case ControllerInput::X:
        dataToModify.report.x += singleDiff->valueDiff;
        break;
    case ControllerInput::Y:
        dataToModify.report.y += singleDiff->valueDiff;
        break;
    case ControllerInput::Z:
        dataToModify.report.z += singleDiff->valueDiff;
        break;
    case ControllerInput::L:
        dataToModify.report.l += singleDiff->valueDiff;
        break;
    case ControllerInput::L_ANALOG:
        dataToModify.report.left += singleDiff->valueDiff;
        break;
    case ControllerInput::R:
        dataToModify.report.r += singleDiff->valueDiff;
        break;
    case ControllerInput::R_ANALOG:
        dataToModify.report.right += singleDiff->valueDiff;
        break;
    case ControllerInput::XAXIS:
        dataToModify.report.xAxis += singleDiff->valueDiff;
        break;
    case ControllerInput::YAXIS:
        dataToModify.report.yAxis += singleDiff->valueDiff;
        break;
    case ControllerInput::C_XAXIS:
        dataToModify.report.cxAxis += singleDiff->valueDiff;
        break;
    case ControllerInput::C_YAXIS:
        dataToModify.report.cyAxis += singleDiff->valueDiff;
        break;
    default:
        Serial.print("Invalid controller input!");
    }
}