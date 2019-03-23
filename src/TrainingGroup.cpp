#include "TrainingGroup.hpp"

TrainingGroup::TrainingGroup(ValidationFunc f, InputModifier **modifiers,
                             uint8_t modifiersSize)
    : validationFunc(f), modifiers(modifiers), currentModifier(0),
      modifiersSize(modifiersSize), inputPressed(false) {}

bool TrainingGroup::checkInputToActivate(Gamecube_Data_t &input) {
    return (validationFunc)(input, this->inputPressed);
}

bool TrainingGroup::hasNextModifier() {
    return currentModifier < modifiersSize;
}

InputModifier *TrainingGroup::getNextModifier() {
    InputModifier *modifierToReturn = modifiers[currentModifier];
    currentModifier++;
    return modifierToReturn;
}

void TrainingGroup::resetModifiers() { currentModifier = 0; }

bool checkDITrainingInput(Gamecube_Data_t &input, bool &buttonPressed) {
    if (buttonPressed && !input.report.dleft) {
        buttonPressed = false;
        return true;
    }
    buttonPressed = input.report.dleft;
    return false;
}

bool checkEOTrainingInput(Gamecube_Data_t &input, bool &buttonPressed) {
    if (buttonPressed && !input.report.dright) {
        buttonPressed = false;
        return true;
    }
    buttonPressed = input.report.dright;
    return false;
}

bool checkOOSTrainingInput(Gamecube_Data_t &input, bool &buttonPressed) {
    if (buttonPressed && !input.report.dleft) {
        buttonPressed = false;
        return input.report.l;
    }
    buttonPressed = input.report.dleft;
    return false;
}

bool checkRecordingTrainingInput(Gamecube_Data_t &input, bool &buttonPressed) {
    if (buttonPressed && !input.report.ddown) {
        buttonPressed = false;
        return true;
    }
    buttonPressed = input.report.ddown;
    return false;
}

bool checkPlaybackTrainingInput(Gamecube_Data_t &input, bool &buttonPressed) {
    if (buttonPressed && !input.report.dup) {
        buttonPressed = false;
        return true;
    }
    buttonPressed = input.report.dup;
    return false;
}
