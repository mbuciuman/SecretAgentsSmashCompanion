#ifndef SASC_INPUTHANDLER_HPP_
#define SASC_INPUTHANDLER_HPP_
#include "Constants.hpp"
#include "InputModifiers/DI/LeftRightDI.hpp"
#include "InputModifiers/DI/RandomDI.hpp"
#include "InputModifiers/EscapeOption/MashAirdodge.hpp"
#include "InputModifiers/EscapeOption/MashJump.hpp"
#include "InputModifiers/InputModifier.hpp"
#include "InputModifiers/NoModifier.hpp"
#include "InputModifiers/Recording/InputPlayback.hpp"
#include "InputModifiers/Recording/InputRecording.hpp"
#include <Nintendo.h>

// static declarations of all modifiers
static NoModifier NO_MODIFIER = NoModifier();
static LeftRightDI LEFT_RIGHT_DI = LeftRightDI();
static RandomDI RANDOM_DI = RandomDI();
static MashAirdodge MASH_AIRDODGE = MashAirdodge();
static MashJump MASH_JUMP = MashJump();
static InputChangeStore INPUT_CHANGE_STORE = InputChangeStore();
static InputRecording INPUT_RECORDING = InputRecording(INPUT_CHANGE_STORE);
static InputPlayback INPUT_PLAYBACK = InputPlayback(INPUT_CHANGE_STORE);

// constants for list size for each direction
static const uint8_t LEFT_MOD_SIZE = 2;
static const uint8_t UP_MOD_SIZE = 1;
static const uint8_t RIGHT_MOD_SIZE = 2;
static const uint8_t DOWN_MOD_SIZE = 1;

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

    void removeDPadInputs(Gamecube_Data_t &data);

  public:
    InputHandler();
    void processInput(Gamecube_Data_t &data);
    void updateCurrentState(Gamecube_Report_t &report);
    void updateDpadButtonState(uint8_t input, bool &dirPressed);
    bool directionReleased(uint8_t input, bool &dirPressed);
    void updateActiveInputModifier(Direction newDirection,
                                   InputModifier *modifiers[],
                                   const uint8_t &maxArraySize);
    InputModifier *getNextModifier(Direction newDirection,
                                   InputModifier *modifiers[],
                                   const uint8_t &maxArraySize);
};
#endif // SASC_INPUTHANDLER_HPP_