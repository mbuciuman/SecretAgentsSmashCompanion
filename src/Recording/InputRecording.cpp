#include "InputRecording.hpp"

InputRecording::InputRecording() {
    this->initialData = NULL;
    this->inputDiffs = new LinkedList<InputDiff>();
}

void InputRecording::startRecording(Gamecube_Data_t *initialData) {
    delete this->inputDiffs;
}

void InputRecording::modifyInput(Gamecube_Data_t *currentData) {}

void InputRecording::cleanUp() {}