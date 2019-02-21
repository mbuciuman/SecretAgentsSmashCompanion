#include "NoInputPlayback.hpp"

NoInputPlayback::~NoInputPlayback() {}

void NoInputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {
    // no Escape Option, so we leave all controller inputs the same
}

void NoInputPlayback::cleanUp() {
    // nothing to do
}