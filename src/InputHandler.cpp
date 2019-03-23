#include "InputHandler.hpp"

// Input modifier definitions
NoModifier NO_MODIFIER = NoModifier();
LeftRightDI LEFT_RIGHT_DI = LeftRightDI();
RandomDI RANDOM_DI = RandomDI();
SetDI SET_DI = SetDI();
LeftRightSDI LEFT_RIGHT_SDI = LeftRightSDI();
RandomSDI RANDOM_SDI = RandomSDI();
SetSDI SET_SDI = SetSDI();
MashJump MASH_JUMP = MashJump();
MashAirdodge MASH_AIRDODGE = MashAirdodge();
InputChangeStore INPUT_CHANGE_STORE = InputChangeStore();
InputRecording INPUT_RECORDING = InputRecording(INPUT_CHANGE_STORE);
InputPlayback INPUT_PLAYBACK = InputPlayback(INPUT_CHANGE_STORE);
UpSmashOOS UP_SMASH_OOS = UpSmashOOS();
UpBOOS UP_B_OOS = UpBOOS();
NairOOS NAIR_OOS = NairOOS();
GrabOOS GRAB_OOS = GrabOOS();

// constants for list size for each training group
const uint8_t DI_TRAINING_SIZE = 6;
const uint8_t OUT_OF_SHIELD_TRAINING_SIZE = 4;
const uint8_t RECORDING_SIZE = 1;
const uint8_t ESCAPE_OPTIONS_TRAINING_SIZE = 2;
const uint8_t PLAYBACK_SIZE = 1;

// the arrays representing each training group's assigned modifiers
InputModifier *diModifiers[DI_TRAINING_SIZE] = {&LEFT_RIGHT_DI, &RANDOM_DI,
                                                &SET_DI,        &LEFT_RIGHT_SDI,
                                                &RANDOM_SDI,    &SET_SDI};
InputModifier *escapeOptionsModifiers[ESCAPE_OPTIONS_TRAINING_SIZE] = {
    &MASH_JUMP, &MASH_AIRDODGE};
InputModifier *outOfShieldModifiers[OUT_OF_SHIELD_TRAINING_SIZE] = {
    &UP_SMASH_OOS, &UP_B_OOS, &NAIR_OOS, &GRAB_OOS};
InputModifier *recordingModifier[RECORDING_SIZE] = {&INPUT_RECORDING};
InputModifier *playbackModifier[PLAYBACK_SIZE] = {&INPUT_PLAYBACK};

/**
 * @brief Construct a new Input Handler:: Input Handler object. This is also
 * where each DPad's direction is given its list of input modifiers.
 *
 */
InputHandler::InputHandler()
    : trainingActive(false),
      diTraining(checkDITrainingInput, diModifiers, DI_TRAINING_SIZE),
      escapeOptionTraining(checkEOTrainingInput, escapeOptionsModifiers,
                           ESCAPE_OPTIONS_TRAINING_SIZE),
      outOfShieldTraining(checkOOSTrainingInput, outOfShieldModifiers,
                          OUT_OF_SHIELD_TRAINING_SIZE),
      recording(checkRecordingTrainingInput, recordingModifier, 1),
      playback(checkPlaybackTrainingInput, playbackModifier, 1),
      currentTraining(&diTraining), activeInputModifier(&NO_MODIFIER) {}

/**
 * @brief Given a controller's data, modifies it based on the active input
 * modifier
 * @param data the reference to the current controller's data
 */
void InputHandler::processInput(Gamecube_Data_t &data) {
    updateCurrentTraining(data);
    updateActiveInputModifier(data);
    activeInputModifier->modifyInput(data);
    removeDPadInputs(data);
}

void InputHandler::updateCurrentTraining(Gamecube_Data_t &data) {
    if (diTraining.checkInputToActivate(data)) {
        currentTraining = &diTraining;
    }
    if (escapeOptionTraining.checkInputToActivate(data)) {
        currentTraining = &escapeOptionTraining;
    }
    if (outOfShieldTraining.checkInputToActivate(data)) {
        currentTraining = &outOfShieldTraining;
    }
    if (recording.checkInputToActivate(data)) {
        currentTraining = &recording;
    }
    if (playback.checkInputToActivate(data)) {
        currentTraining = &playback;
    }
}

void InputHandler::updateActiveInputModifier(Gamecube_Data_t &data) {
    if (currentTraining->hasNextModifier()) {
        activeInputModifier = currentTraining->getNextModifier();
    } else {
        currentTraining->resetModifiers();
        activeInputModifier = &NO_MODIFIER;
    }
}