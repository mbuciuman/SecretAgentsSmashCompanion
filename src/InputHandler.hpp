#ifndef SASC_INPUTHANDLER_HPP_
#define SASC_INPUTHANDLER_HPP_
#include "Constants.hpp"
#include "Utility.hpp"
#include "InputModifiers/DI/LeftRightDI.hpp"
#include "InputModifiers/DI/RandomDI.hpp"
#include "InputModifiers/EscapeOption/MashAirdodge.hpp"
#include "InputModifiers/EscapeOption/MashJump.hpp"
#include "InputModifiers/InputModifier.hpp"
#include "InputModifiers/NoModifier.hpp"
#include "InputModifiers/Recording/InputPlayback.hpp"
#include "InputModifiers/Recording/InputRecording.hpp"
#include <Nintendo.h>

// declarations of all input modifiers
extern NoModifier NO_MODIFIER;
extern LeftRightDI LEFT_RIGHT_DI;
extern RandomDI RANDOM_DI;
extern MashAirdodge MASH_AIRDODGE;
extern MashJump MASH_JUMP;
extern InputChangeStore INPUT_CHANGE_STORE;
extern InputRecording INPUT_RECORDING;
extern InputPlayback INPUT_PLAYBACK;

// constants for list size for each direction
const uint8_t LEFT_MOD_SIZE = 2;
const uint8_t UP_MOD_SIZE = 1;
const uint8_t RIGHT_MOD_SIZE = 2;
const uint8_t DOWN_MOD_SIZE = 1;

/**
 * @brief Modifies given controller input based on internal state
 *
 * This class is the logic center which handles selecting the active input
 * modifier (a.k.a. training modifier). Each DPad input has a list of input
 * modifiers associated with it.
 *
 * When the user taps a DPad direction, the active input modifier changes to the
 * first modifier assigned to that DPad. When the user taps that same DPad
 * direction again, the active input modifier cycles to the next input modifier
 * assigned to the DPad. If the user taps the DPad in a direction different than
 * the previous DPad button press, or if the user reaches the end of the input
 * modifiers assigned to the existing DPad's button, then the active input
 * modifier cycles back to the original behavior which is to pass-through all
 * inputs.
 */
class InputHandler {
  private:
    // booleans representing button states
    bool leftPressed;
    bool upPressed;
    bool rightPressed;
    bool downPressed;

    // the index of the current Dpad direction's modifier list
    uint8_t currentIndex;
    // the current DPad direction
    Direction currentDirection;

    // the arrays representing each DPad direction's assinged modifiers
    InputModifier *leftModifiers[LEFT_MOD_SIZE];
    InputModifier *upModifiers[UP_MOD_SIZE];
    InputModifier *rightModifiers[RIGHT_MOD_SIZE];
    InputModifier *downModifiers[DOWN_MOD_SIZE];

    // Currently active input modifier (there's only one at a time)
    InputModifier *activeInputModifier;

  public:
    InputHandler();
    void processInput(Gamecube_Data_t &data);
    void updateCurrentState(Gamecube_Report_t &report);
    void updateDpadButtonState(const uint8_t input, bool &dirPressed);
    bool directionReleased(const uint8_t input, const bool dirPressed);
    void updateActiveInputModifier(const Direction newDirection,
                                   InputModifier *modifiers[],
                                   const uint8_t maxArraySize);
    InputModifier *getNextModifier(const Direction newDirection,
                                   InputModifier *modifiers[],
                                   const uint8_t maxArraySize);
};
#endif // SASC_INPUTHANDLER_HPP_