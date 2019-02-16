#include "NoEscapeOption.hpp"

NoEscapeOption::~NoEscapeOption() {}

void NoEscapeOption::modifyInput(Gamecube_Data_t &dataToModify) {
    // no Escape Option, so we leave all controller inputs the same
}

void NoEscapeOption::cleanUp() {
    // nothing to do
}