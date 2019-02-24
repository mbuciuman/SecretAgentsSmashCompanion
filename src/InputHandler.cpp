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
}

/**
 * Update the handler's state given the Gamecube controller report
 */
void InputHandler::updateCurrentState(Gamecube_Report_t &report) {
    // update active input modifier based on DPad changes
    if (directionReleased(report.dleft, leftPressed)) {
        Serial.println(F("le_re"));
        updateActiveInputModifier(Direction::LEFT, leftModifiers,
                                  LEFT_MOD_SIZE);
    }
    if (directionReleased(report.dup, upPressed)) {
        Serial.println(F("up_re"));
        updateActiveInputModifier(Direction::UP, upModifiers, UP_MOD_SIZE);
    }
    if (directionReleased(report.dright, rightPressed)) {
        Serial.println(F("ri_re"));
        updateActiveInputModifier(Direction::RIGHT, rightModifiers,
                                  RIGHT_MOD_SIZE);
    }
    if (directionReleased(report.ddown, downPressed)) {
        Serial.println(F("do_re"));
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
    if (currentDirection == newDirection) {
#ifdef DEBUG
        Serial.println(F("Current direction equals new direction"));
#endif
        if (currentIndex + 1 < maxArraySize) {
#ifdef DEBUG
            Serial.println(F("Advancing"));
#endif
            currentIndex++;
            return modifiers[currentIndex];
        } else {
#ifdef DEBUG
            Serial.println(F("Reached end of direction, RESETTING"));
#endif
            currentDirection = Direction::NO_DIR;
            currentIndex = 0;
            return &noModifier;
        }
    } else {
#ifdef DEBUG
        Serial.println(F("New direction is diferent from current direction!"));
#endif
        currentDirection = newDirection;
        currentIndex = 0;
        return modifiers[currentIndex];
    }
}
