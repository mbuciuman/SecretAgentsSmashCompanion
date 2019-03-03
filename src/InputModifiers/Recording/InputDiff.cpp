#include "InputDiff.hpp"

/**
 * @brief Construct a new Input Diff:: Input Diff object
 */
InputDiff::InputDiff() : timeDiff(0), singleDiffs{} {}

/**
 * @brief Initializes (or re-initializes) this input diff
 *
 * @param timeDiff time elapsed between controller inputs in ms.
 * @param firstReport the first controller input report
 * @param secondReport the second controller input report
 */
void InputDiff::initialize(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                           Gamecube_Report_t &secondReport) {
    reset();
    this->timeDiff = timeDiff;
    storeDiffs(firstReport, secondReport);
}

/**
 * @brief Stores the diffs between both controller reports
 */
void InputDiff::storeDiffs(Gamecube_Report_t &firstReport,
                           Gamecube_Report_t &secondReport) {
    // NOTE: Arrays below SHOULD LINE UP between all inputs
    uint8_t firstReportInputs[] = {
        firstReport.a,     firstReport.b,     firstReport.x,
        firstReport.y,     firstReport.z,     firstReport.l,
        firstReport.left,  firstReport.r,     firstReport.right,
        firstReport.xAxis, firstReport.yAxis, firstReport.cxAxis,
        firstReport.cyAxis};
    uint8_t secondReportInputs[] = {
        secondReport.a,     secondReport.b,     secondReport.x,
        secondReport.y,     secondReport.z,     secondReport.l,
        secondReport.left,  secondReport.r,     secondReport.right,
        secondReport.xAxis, secondReport.yAxis, secondReport.cxAxis,
        secondReport.cyAxis};
    ControllerInput associatedInputs[] = {
        ControllerInput::A,        ControllerInput::B,
        ControllerInput::X,        ControllerInput::Y,
        ControllerInput::Z,        ControllerInput::L,
        ControllerInput::L_ANALOG, ControllerInput::R,
        ControllerInput::R_ANALOG, ControllerInput::XAXIS,
        ControllerInput::YAXIS,    ControllerInput::C_XAXIS,
        ControllerInput::C_YAXIS};
    for (int i = 0; i < MAX_SINGLE_INPUT_DIFFS; i++) {
        if (inputsDiffer(firstReportInputs[i], secondReportInputs[i],
                         associatedInputs[i])) {
            storeSingleDiff(firstReportInputs[i], secondReportInputs[i],
                            associatedInputs[i]);
        }
    }
}

/**
 * @brief Determines whether the two inputs given the associated buttons differ.
 * NOTE: this method was created in case specific logic needed to be added for
 * certain input diffs.
 *
 * @param first first input value
 * @param second second input value
 * @param input the associated input type
 * @return true the inputs differ significantly
 * @return false the inputs do not differ significantly
 */
bool InputDiff::inputsDiffer(uint8_t first, uint8_t second,
                             ControllerInput input) {
    return abs(second - first) > 0;
}

/**
 * @brief Resets this object to initial values.
 */
void InputDiff::reset() {
    // reset diff by storing dummy diffs in each element
    for (int i = 0; i < MAX_SINGLE_INPUT_DIFFS; i++) {
        singleDiffs[i].input = ControllerInput::A;
        singleDiffs[i].valueDiff = 0;
    }
}

/**
 * @brief Helper method to store a single input's diff.
 *
 * @param firstVal the first input value
 * @param secondVal the second input value
 * @param input the associated input type
 */
void InputDiff::storeSingleDiff(uint8_t firstVal, uint8_t secondVal,
                                ControllerInput input) {
    int16_t diff = (int16_t)secondVal - (int16_t)firstVal;
    this->singleDiffs[(int)input] = (SingleInputDiff){input, diff};
}

/**
 * @brief Returns the time elapsed between diffs in ms.
 */
uint16_t InputDiff::getTimeDiff() { return timeDiff; }

/**
 * @brief Applies this stored diff to a given reference of a controller's data.
 *
 * @param dataToModify a given controller's data
 */
void InputDiff::applyTo(Gamecube_Data_t &dataToModify) {
    for (int i = 0; i < MAX_SINGLE_INPUT_DIFFS; i++) {
        applySingleDiffTo(singleDiffs[i], dataToModify);
    }
}

/**
 * @brief Helper method which applies a single input's diff to a given reference
 * of a controller's data.
 *
 * @param singleInputDiff the single input diff to apply
 * @param dataToModify a given controller's data
 */
void InputDiff::applySingleDiffTo(SingleInputDiff &singleInputDiff,
                                  Gamecube_Data_t &dataToModify) {
    switch (singleInputDiff.input) {
    case ControllerInput::A:
        dataToModify.report.a += singleInputDiff.valueDiff;
        break;
    case ControllerInput::B:
        dataToModify.report.b += singleInputDiff.valueDiff;
        break;
    case ControllerInput::X:
        dataToModify.report.x += singleInputDiff.valueDiff;
        break;
    case ControllerInput::Y:
        dataToModify.report.y += singleInputDiff.valueDiff;
        break;
    case ControllerInput::Z:
        dataToModify.report.z += singleInputDiff.valueDiff;
        break;
    case ControllerInput::L:
        dataToModify.report.l += singleInputDiff.valueDiff;
        break;
    case ControllerInput::L_ANALOG:
        dataToModify.report.left += singleInputDiff.valueDiff;
        break;
    case ControllerInput::R:
        dataToModify.report.r += singleInputDiff.valueDiff;
        break;
    case ControllerInput::R_ANALOG:
        dataToModify.report.right += singleInputDiff.valueDiff;
        break;
    case ControllerInput::XAXIS:
        dataToModify.report.xAxis += singleInputDiff.valueDiff;
        break;
    case ControllerInput::YAXIS:
        dataToModify.report.yAxis += singleInputDiff.valueDiff;
        break;
    case ControllerInput::C_XAXIS:
        dataToModify.report.cxAxis += singleInputDiff.valueDiff;
        break;
    case ControllerInput::C_YAXIS:
        dataToModify.report.cyAxis += singleInputDiff.valueDiff;
        break;
    default:
#ifdef DEBUG
        Serial.print(F("Invalid controller input!"));
#endif
        break;
    }
}