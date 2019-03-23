#ifndef SASC_INPUTHANDLER_HPP_
#define SASC_INPUTHANDLER_HPP_
#include "Constants.hpp"
#include "InputModifiers/DI/LeftRightDI.hpp"
#include "InputModifiers/DI/LeftRightSDI.hpp"
#include "InputModifiers/DI/RandomDI.hpp"
#include "InputModifiers/DI/RandomSDI.hpp"
#include "InputModifiers/DI/SetDI.hpp"
#include "InputModifiers/DI/SetSDI.hpp"
#include "InputModifiers/EscapeOption/MashAirdodge.hpp"
#include "InputModifiers/EscapeOption/MashJump.hpp"
#include "InputModifiers/InputModifier.hpp"
#include "InputModifiers/NoModifier.hpp"
#include "InputModifiers/OOSOptions/GrabOOS.hpp"
#include "InputModifiers/OOSOptions/NairOOS.hpp"
#include "InputModifiers/OOSOptions/UpBOOS.hpp"
#include "InputModifiers/OOSOptions/UpSmashOOS.hpp"
#include "InputModifiers/Recording/InputPlayback.hpp"
#include "InputModifiers/Recording/InputRecording.hpp"
#include "TrainingGroup.hpp"
#include "Utility.hpp"
#include <Nintendo.h>

// declarations of all input modifiers
extern NoModifier NO_MODIFIER;
extern LeftRightDI LEFT_RIGHT_DI;
extern RandomDI RANDOM_DI;
extern SetDI SET_DI;
extern LeftRightSDI LEFT_RIGHT_SDI;
extern RandomSDI RANDOM_SDI;
extern SetSDI SET_SDI;
extern MashAirdodge MASH_AIRDODGE;
extern MashJump MASH_JUMP;
extern InputChangeStore INPUT_CHANGE_STORE;
extern InputRecording INPUT_RECORDING;
extern InputPlayback INPUT_PLAYBACK;
extern UpSmashOOS UP_SMASH_OOS;
extern UpBOOS UP_B_OOS;
extern NairOOS NAIR_OOS;
extern GrabOOS GRAB_OOS;

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
    bool trainingActive;

    TrainingGroup diTraining;
    TrainingGroup escapeOptionTraining;
    TrainingGroup outOfShieldTraining;
    TrainingGroup recording;
    TrainingGroup playback;

    TrainingGroup *currentTraining;

    // Currently active input modifier (there's only one at a time)
    InputModifier *activeInputModifier;

  public:
    InputHandler();
    void processInput(Gamecube_Data_t &data);
    void updateCurrentState(Gamecube_Data_t &data);
    void updateCurrentTraining(Gamecube_Data_t &data);
    void updateActiveInputModifier(Gamecube_Data_t &data);
};
#endif // SASC_INPUTHANDLER_HPP_