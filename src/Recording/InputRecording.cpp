#include "InputRecording.hpp"

InputRecording::InputRecording()
    : initialData(NULL), inputDiffs(new LinkedList<InputDiff>()) {}

InputRecording::~InputRecording() {
    delete initialData;
    delete inputDiffs;
}

void InputRecording::startRecording(Gamecube_Data_t *initialData) {}

void InputRecording::modifyInput(Gamecube_Data_t *currentData) {}

void InputRecording::cleanUp() {}