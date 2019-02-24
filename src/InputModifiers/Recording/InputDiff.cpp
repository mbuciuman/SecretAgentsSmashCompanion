#include "InputDiff.hpp"

InputDiff::InputDiff() : timeDiff(0), singleDiffs{} {}

void InputDiff::initialize(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                           Gamecube_Report_t &secondReport) {
    this->timeDiff = timeDiff;
    storeDiffs(firstReport, secondReport);
}

void InputDiff::storeDiffs(Gamecube_Report_t &firstReport,
                           Gamecube_Report_t &secondReport) {
    storeSingleDiff(firstReport.a, secondReport.a, ControllerInput::A);
    storeSingleDiff(firstReport.b, secondReport.b, ControllerInput::B);
    storeSingleDiff(firstReport.x, secondReport.x, ControllerInput::X);
    storeSingleDiff(firstReport.y, secondReport.y, ControllerInput::Y);
    storeSingleDiff(firstReport.z, secondReport.z, ControllerInput::Z);
    storeSingleDiff(firstReport.l, secondReport.l, ControllerInput::L);
    storeSingleDiff(firstReport.left, secondReport.left,
                    ControllerInput::L_ANALOG);
    storeSingleDiff(firstReport.r, secondReport.r, ControllerInput::R);
    storeSingleDiff(firstReport.right, secondReport.right,
                    ControllerInput::R_ANALOG);
    storeSingleDiff(firstReport.xAxis, secondReport.xAxis,
                    ControllerInput::XAXIS);
    storeSingleDiff(firstReport.yAxis, secondReport.yAxis,
                    ControllerInput::YAXIS);
    storeSingleDiff(firstReport.cxAxis, secondReport.cxAxis,
                    ControllerInput::C_XAXIS);
    storeSingleDiff(firstReport.cyAxis, secondReport.cyAxis,
                    ControllerInput::C_YAXIS);
}

void InputDiff::storeSingleDiff(uint8_t firstVal, uint8_t secondVal,
                                ControllerInput input) {
    int16_t diff = (int16_t)firstVal - (int16_t)secondVal;
    this->singleDiffs[(int)input] = (SingleInputDiff){input, diff};
}

uint16_t InputDiff::getTimeDiff() { return timeDiff; }

void InputDiff::applyTo(Gamecube_Data_t &dataToModify) {
    for (int i = 0; i < (int)ControllerInput::TOTAL_INPUTS; i++) {
        singleDiffs[i].applyTo(dataToModify);
    }
}

void SingleInputDiff::applyTo(Gamecube_Data_t &dataToModify) {
    switch (input) {
    case ControllerInput::A:
        dataToModify.report.a += valueDiff;
        break;
    case ControllerInput::B:
        dataToModify.report.b += valueDiff;
        break;
    case ControllerInput::X:
        dataToModify.report.x += valueDiff;
        break;
    case ControllerInput::Y:
        dataToModify.report.y += valueDiff;
        break;
    case ControllerInput::Z:
        dataToModify.report.z += valueDiff;
        break;
    case ControllerInput::L:
        dataToModify.report.l += valueDiff;
        break;
    case ControllerInput::L_ANALOG:
        dataToModify.report.left += valueDiff;
        break;
    case ControllerInput::R:
        dataToModify.report.r += valueDiff;
        break;
    case ControllerInput::R_ANALOG:
        dataToModify.report.right += valueDiff;
        break;
    case ControllerInput::XAXIS:
        dataToModify.report.xAxis += valueDiff;
        break;
    case ControllerInput::YAXIS:
        dataToModify.report.yAxis += valueDiff;
        break;
    case ControllerInput::C_XAXIS:
        dataToModify.report.cxAxis += valueDiff;
        break;
    case ControllerInput::C_YAXIS:
        dataToModify.report.cyAxis += valueDiff;
        break;
    default:
        Serial.print(F("Invalid controller input!"));
    }
}