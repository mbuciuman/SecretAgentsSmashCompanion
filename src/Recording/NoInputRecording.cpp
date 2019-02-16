#include "NoInputRecording.hpp"

NoInputRecording::~NoInputRecording() {}

void NoInputRecording::modifyInput(Gamecube_Data_t &dataToModify) {
    // no Escape Option, so we leave all controller inputs the same
}

void NoInputRecording::cleanUp() {
    // nothing to do
}