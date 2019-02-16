#include "InputRecording.hpp"

InputRecording::InputRecording()
    : initialData(Gamecube_Data_t()), inputDiffs(new LinkedList<InputDiff>()) {}

InputRecording::~InputRecording() { delete inputDiffs; }

void InputRecording::startRecording(Gamecube_Data_t &initialData) {}

void InputRecording::modifyInput(Gamecube_Data_t &currentData) {}

LinkedList<InputDiff> *InputRecording::getInputDiffs() { return inputDiffs; }

void InputRecording::cleanUp() {}