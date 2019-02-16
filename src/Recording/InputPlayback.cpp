#include "InputPlayback.hpp"

InputPlayback::InputPlayback() {}

InputPlayback::~InputPlayback() {}

void InputPlayback::initialize(Gamecube_Data_t &initialData,
                               LinkedList<InputDiff> *inputDiffs) {
    this->initialData = initialData;
    this->inputDiffs = inputDiffs;
}

void InputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {}

void InputPlayback::cleanUp() {}