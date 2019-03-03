#include "InputHandler.hpp"

InputHandler::InputHandler()
    : leftPressed(false), upPressed(false), rightPressed(false),
      downPressed(false), currentIndex(0), currentDirection(Direction::NO_DIR),
      leftModifiers{&leftRightDI, &randomDI}, upModifiers{&inputPlayback},
      rightModifiers{&mashJump, &mashAirdodge}, downModifiers{&inputRecording},
      activeInputModifier(&noModifier) {}

/**
 * Given a controller's data, modifies it based on the active input modifier
 */
void InputHandler::processInput(Gamecube_Data_t &data) {
    updateCurrentState(data.report);
    activeInputModifier->modifyInput(data);
    removeDPadInputs(data);
}

/**
 * Update the handler's state given the Gamecube controller report
 */
void InputHandler::updateCurrentState(Gamecube_Report_t &report) {
    // update active input modifier based on DPad changes
    if (directionReleased(report.dleft, leftPressed)) {
#ifdef DEBUG
        Serial.println(F("le_re"));
#endif
        updateActiveInputModifier(Direction::LEFT, leftModifiers,
                                  LEFT_MOD_SIZE);
    }
    if (directionReleased(report.dup, upPressed)) {
#ifdef DEBUG
        Serial.println(F("up_re"));
#endif
        updateActiveInputModifier(Direction::UP, upModifiers, UP_MOD_SIZE);
    }
    if (directionReleased(report.dright, rightPressed)) {
#ifdef DEBUG
        Serial.println(F("ri_re"));
#endif
        updateActiveInputModifier(Direction::RIGHT, rightModifiers,
                                  RIGHT_MOD_SIZE);
    }
    if (directionReleased(report.ddown, downPressed)) {
#ifdef DEBUG
        Serial.println(F("do_re"));
#endif
        updateActiveInputModifier(Direction::DOWN, downModifiers,
                                  DOWN_MOD_SIZE);
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
void InputHandler::updateActiveInputModifier(Direction newDirection,
                                             InputModifier *modifiers[],
                                             const uint8_t &maxArraySize) {
    activeInputModifier->cleanUp();
    activeInputModifier =
        getNextModifier(newDirection, modifiers, maxArraySize);
}

/**
 * Get the next input modifier from the given list and its current iterator
 */
InputModifier *InputHandler::getNextModifier(Direction newDirection,
                                             InputModifier *modifiers[],
                                             const uint8_t &maxArraySize) {
    if (currentDirection == newDirection && currentIndex + 1 < maxArraySize) {
        currentIndex++;
        return modifiers[currentIndex];
    } else if (currentDirection == Direction::NO_DIR) {
        currentDirection = newDirection;
        currentIndex = 0;
        return modifiers[currentIndex];
    } else {
        currentDirection = Direction::NO_DIR;
        currentIndex = 0;
        return &noModifier;
    }
}

void InputHandler::removeDPadInputs(Gamecube_Data_t &dataToModify) {
    dataToModify.report.dleft = 0;
    dataToModify.report.dup = 0;
    dataToModify.report.dright = 0;
    dataToModify.report.ddown = 0;
}
