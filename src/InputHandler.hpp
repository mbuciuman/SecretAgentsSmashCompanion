#ifndef GCTRAIN_INPUTHANDLER_HPP_
#define GCTRAIN_INPUTHANDLER_HPP_
#include "InputModifiers/DI/LeftRightDI.hpp"
#include "InputModifiers/DI/NoDI.hpp"
#include "InputModifiers/DI/RandomDI.hpp"
#include "InputModifiers/EscapeOption/MashAirdodge.hpp"
#include "InputModifiers/EscapeOption/MashJump.hpp"
#include "InputModifiers/EscapeOption/NoEscapeOption.hpp"
#include "InputModifiers/InputModifier.hpp"
#include "InputModifiers/Recording/InputPlayback.hpp"
#include "InputModifiers/Recording/InputRecording.hpp"
#include "InputModifiers/Recording/NoInputPlayback.hpp"
#include "InputModifiers/Recording/NoInputRecording.hpp"
#include "constants.hpp"
#include <Nintendo.h>
#include <linked_list.h>

class InputHandler {
  private:
    bool upPressed;
    bool rightPressed;
    bool downPressed;
    bool leftPressed;

    // DI vars
    LinkedList<InputModifier> allDI;
    Iterator<InputModifier> *itDI;

    // Escape Option vars
    LinkedList<InputModifier> allEscapeOptions;
    Iterator<InputModifier> *itEscapeOption;

    // Input Recording vars
    LinkedList<InputModifier> inputRecordingOptions;
    Iterator<InputModifier> *itInputRecording;

    // Input Playback vars
    LinkedList<InputModifier> inputPlaybackOptions;
    Iterator<InputModifier> *itInputPlayback;

    // Currently active input modifier (there's only one at a time)
    InputModifier *activeInputModifier;

  public:
    InputHandler();
    void processInput(Gamecube_Data_t &data);
    void updateCurrentState(Gamecube_Report_t &report);
    bool directionReleased(uint8_t input, bool &dirPressed);
    void updateActiveInputModifier(LinkedList<InputModifier> &modifiers,
                                   Iterator<InputModifier> *it);
    InputModifier *getNextModifier(LinkedList<InputModifier> &modifiers,
                                   Iterator<InputModifier> *it);
};
#endif // GCTRAIN_INPUTHANDLER_HPP_