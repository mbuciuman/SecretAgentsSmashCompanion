#include "InputDiff.hpp"

InputDiff::InputDiff(long timeDiff, Gamecube_Data_t *firstData,
                     Gamecube_Data_t *secondData) {
    this->timeDiff = timeDiff;
    this->inputDiffs = this->createDiffs(firstData, secondData);
}

LinkedList<SingleInputDiff> *
InputDiff::createDiffs(Gamecube_Data_t *firstData,
                       Gamecube_Data_t *secondData) {
    LinkedList<SingleInputDiff> *inputDiffsList =
        new LinkedList<SingleInputDiff>();
    if (firstData->report.a != secondData->report.a) {
        uint8_t firstA = firstData->report.a;
        uint8_t secondA = secondData->report.a;
        int8_t diff = (int8_t)secondA - (int8_t)firstA;
        SingleInputDiff *singleInputDiff = new SingleInputDiff;
        singleInputDiff->input = ControllerInput::A;
        singleInputDiff->valueDiff = diff;
        inputDiffsList->add(singleInputDiff);
    }
    return inputDiffsList;
}
