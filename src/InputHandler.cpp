#include "InputHandler.hpp"

InputHandler::InputHandler()
    : upPressed(false), rightPressed(false), downPressed(false),
      leftPressed(false), allDI(LinkedList<InputModifier>()), itDI(allDI.it()),
      allEscapeOptions(LinkedList<InputModifier>()),
      itEscapeOption(allEscapeOptions.it()),
      inputRecordingOptions(LinkedList<InputModifier>()),
      itInputRecording(inputRecordingOptions.it()),
      inputPlaybackOptions(LinkedList<InputModifier>()),
      itInputPlayback(inputPlaybackOptions.it()) {
    allDI.add(new NoDI());
    allDI.add(new LeftRightDI());
    allDI.add(new RandomDI());

    allEscapeOptions.add(new NoEscapeOption());
    allEscapeOptions.add(new MashJump());
    allEscapeOptions.add(new MashAirdodge());

    inputRecordingOptions.add(new NoInputRecording());
    inputRecordingOptions.add(new InputRecording());

    inputPlaybackOptions.add(new NoInputPlayback());
    inputPlaybackOptions.add(new InputPlayback());

    // Set up starting active input modifier
    activeInputModifier = itDI->current();
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
    if (directionReleased(report.dup, upPressed)) {
        updateActiveInputModifier(inputPlaybackOptions, itInputPlayback);
    }
    if (directionReleased(report.dright, rightPressed)) {
        updateActiveInputModifier(allEscapeOptions, itEscapeOption);
    }
    if (directionReleased(report.ddown, downPressed)) {
        updateActiveInputModifier(inputRecordingOptions, itInputRecording);
    }
    if (directionReleased(report.dleft, leftPressed)) {
        updateActiveInputModifier(allDI, itDI);
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
