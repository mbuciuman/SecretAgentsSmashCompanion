#include "InputHandler.hpp"

// Input modifier definitions
NoModifier NO_MODIFIER = NoModifier();
LeftRightDI LEFT_RIGHT_DI = LeftRightDI();
RandomDI RANDOM_DI = RandomDI();
MashJump MASH_JUMP = MashJump();
MashAirdodge MASH_AIRDODGE = MashAirdodge();
InputChangeStore INPUT_CHANGE_STORE = InputChangeStore();
InputRecording INPUT_RECORDING = InputRecording(INPUT_CHANGE_STORE);
InputPlayback INPUT_PLAYBACK = InputPlayback(INPUT_CHANGE_STORE);

/**
 * @brief Construct a new Input Handler:: Input Handler object. This is also
 * where each DPad's direction is given its list of input modifiers.
 *
 */
InputHandler::InputHandler()
    : leftPressed(false), upPressed(false), rightPressed(false),
      downPressed(false), currentIndex(0),
      currentDirection(Direction::NO_DIR), leftModifiers{&LEFT_RIGHT_DI,
                                                         &RANDOM_DI},
      upModifiers{&INPUT_PLAYBACK}, rightModifiers{&MASH_JUMP, &MASH_AIRDODGE},
      downModifiers{&INPUT_RECORDING}, activeInputModifier(&NO_MODIFIER) {}

/**
 * @brief Given a controller's data, modifies it based on the active input
 * modifier
 * @param data the reference to the current controller's data
 */
void InputHandler::processInput(Gamecube_Data_t &data) {
    updateCurrentState(data.report);
    activeInputModifier->modifyInput(data);
    removeDPadInputs(data);
}

/**
 * @brief Update the handler's state given the Gamecube controller report
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
    updateDpadButtonState(report.dleft, leftPressed);
    updateDpadButtonState(report.dup, upPressed);
    updateDpadButtonState(report.ddown, downPressed);
    updateDpadButtonState(report.dright, rightPressed);
}

void InputHandler::updateDpadButtonState(const uint8_t input, bool dirPressed) {
    dirPressed = input != 1;
}

/**
 * @brief Checks to see if the given DPad input was released
 */
bool InputHandler::directionReleased(const uint8_t input,
                                     const bool dirPressed) {
    return input != 1 && dirPressed;
}

/**
 * @brief Update the active input modifier given the list of input modifiers and
 * its iterator
 */
void InputHandler::updateActiveInputModifier(const Direction newDirection,
                                             InputModifier *modifiers[],
                                             const uint8_t maxArraySize) {
    activeInputModifier->cleanUp();
    activeInputModifier =
        getNextModifier(newDirection, modifiers, maxArraySize);
}

/**
 * @brief Get the next input modifier from the given list and its current
 * iterator
 */
InputModifier *InputHandler::getNextModifier(const Direction newDirection,
                                             InputModifier *modifiers[],
                                             const uint8_t maxArraySize) {
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
        return &NO_MODIFIER;
    }
}
