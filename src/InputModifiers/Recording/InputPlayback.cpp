#include "InputPlayback.hpp"

InputPlayback::InputPlayback(InputRecording *inputRecording)
    : initialData(Gamecube_Data_t()), playingBack(false), timeElapsed(0),
      inputRecording(inputRecording),
      itDiff(inputRecording->getInputDiffs()->it()) {}

InputPlayback::~InputPlayback() {}

void InputPlayback::initialize(Gamecube_Data_t &initialData) {
    this->initialData = initialData;
    timeElapsed = 0;
    itDiff->reset();
}

void InputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {
    if (!playingBack) {
        initialize(dataToModify);
    } else if (canApplyNextDiff()) {
        applyNextDiff(dataToModify);
    }
}

bool InputPlayback::canApplyNextDiff() {
    if (itDiff->current() == nullptr) {
        playingBack = false;
        return false;
    }
    InputDiff *nextDiff = itDiff->current();
    if (timeElapsed > nextDiff->getTimeDiff()) {
        return true;
    }
    return false;
}

void InputPlayback::applyNextDiff(Gamecube_Data_t &dataToModify) {
    InputDiff *nextDiff = itDiff->current();
    timeElapsed -= nextDiff->getTimeDiff();
    nextDiff->applyDiff(dataToModify);
}

void InputPlayback::cleanUp() { playingBack = false; }