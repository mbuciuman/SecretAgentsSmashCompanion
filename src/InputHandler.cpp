#include "InputHandler.hpp"

InputHandler::InputHandler()
    : upPressed(false), rightPressed(false), downPressed(false),
      leftPressed(false), leftModifiers(LinkedList<InputModifier>()),
      itLeft(leftModifiers.it()), upModifiers(LinkedList<InputModifier>()),
      itUp(upModifiers.it()), rightModifiers(LinkedList<InputModifier>()),
      itRight(rightModifiers.it()), downModifiers(LinkedList<InputModifier>()),
      itDown(downModifiers.it()) {

    // add DI modifiers to left DPad
    leftModifiers.add(new NoDI());
    leftModifiers.add(new LeftRightDI());
    leftModifiers.add(new RandomDI());

    // add Escape Options to right DPad
    rightModifiers.add(new NoEscapeOption());
    rightModifiers.add(new MashJump());
    rightModifiers.add(new MashAirdodge());

    // add input recording to down DPad
    downModifiers.add(new NoInputRecording());
    InputRecording *inputRecording = new InputRecording();
    downModifiers.add(inputRecording);

    // add input playback to up DPad
    upModifiers.add(new NoInputPlayback());
    upModifiers.add(new InputPlayback(inputRecording));

    // Set up starting active input modifier
    activeInputModifier = itLeft->current();
}

/**
 * Given a controller's data, modifies it based on the active input modifier
 */
void InputHandler::processInput(Gamecube_Data_t &data) {
    updateCurrentState(data.report);
    activeInputModifier->modifyInput(data);
}

/**
 * Update the handler's state given the Gamecube controller report
 */
void InputHandler::updateCurrentState(Gamecube_Report_t &report) {
    // update active input modifier based on DPad changes
    if (directionReleased(report.dleft, leftPressed)) {
        updateActiveInputModifier(leftModifiers, itLeft);
    }
    if (directionReleased(report.dup, upPressed)) {
        updateActiveInputModifier(upModifiers, itUp);
    }
    if (directionReleased(report.dright, rightPressed)) {
        updateActiveInputModifier(rightModifiers, itRight);
    }
    if (directionReleased(report.ddown, downPressed)) {
        updateActiveInputModifier(downModifiers, itDown);
    }
}

/**
 * Checks to see if the given DPad input was released
 */
bool InputHandler::directionReleased(uint8_t input, bool &dirPressed) {
    if (input == 1) {
        // direction is pressed if input is high
        dirPressed = true;
    } else if (dirPressed) {
        // direction released if input is now low but was previously high
        dirPressed = false;
        return true;
    }
    return false;
}

/**
 * Update the active input modifier given the list of input modifiers and its
 * iterator
 */
void InputHandler::updateActiveInputModifier(
    LinkedList<InputModifier> &modifiers, Iterator<InputModifier> *it) {
    activeInputModifier->cleanUp();
    activeInputModifier = getNextModifier(modifiers, it);
}

/**
 * Get the next input modifier from the given list and its current iterator
 */
InputModifier *
InputHandler::getNextModifier(LinkedList<InputModifier> &modifiers,
                              Iterator<InputModifier> *it) {
    if (modifiers.contains(activeInputModifier)) {
        // return the next input modifier in the given list
        if (!it->moveNext()) {
            it->reset();
        }
    } else {
        // return the first input modifier in the given list
        it->reset();
    }
    return it->current();
}
