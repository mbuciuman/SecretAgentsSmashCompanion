#include "InputDiff.hpp"

InputDiff::InputDiff(long timeDiff, Gamecube_Report_t &firstReport,
                     Gamecube_Report_t &secondReport)
    : timeDiff(timeDiff), inputDiffs(new LinkedList<SingleInputDiff>()) {
    initialize(firstReport, secondReport);
}

InputDiff::~InputDiff() { delete inputDiffs; }

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
        int8_t diff = (int8_t)firstVal - (int8_t)secondVal;
        SingleInputDiff *singleInputDiff = new SingleInputDiff;
        singleInputDiff->input = input;
        singleInputDiff->valueDiff = diff;
        inputDiffs->add(singleInputDiff);
    }
}