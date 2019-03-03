#ifndef GCTRAIN_INPUTHANDLER_HPP_
#define GCTRAIN_INPUTHANDLER_HPP_
#include "InputModifiers/DI/LeftRightDI.hpp"
#include "InputModifiers/DI/RandomDI.hpp"
#include "InputModifiers/EscapeOption/MashAirdodge.hpp"
#include "InputModifiers/EscapeOption/MashJump.hpp"
#include "InputModifiers/InputModifier.hpp"
#include "InputModifiers/NoModifier.hpp"
#include "InputModifiers/Recording/InputPlayback.hpp"
#include "InputModifiers/Recording/InputRecording.hpp"
#include "constants.hpp"
#include <Nintendo.h>

static NoModifier noModifier = NoModifier();
static LeftRightDI leftRightDI = LeftRightDI();
static RandomDI randomDI = RandomDI();
static MashAirdodge mashAirdodge = MashAirdodge();
static MashJump mashJump = MashJump();
static InputRecording inputRecording = InputRecording();
static InputPlayback inputPlayback =
    InputPlayback(inputRecording.getInputDiffStore());

static const uint8_t LEFT_MOD_SIZE = 2;
static const uint8_t UP_MOD_SIZE = 1;
static const uint8_t RIGHT_MOD_SIZE = 2;
static const uint8_t DOWN_MOD_SIZE = 1;

class InputHandler {
  private:
    bool leftPressed;
    bool upPressed;
    bool rightPressed;
    bool downPressed;

    uint8_t currentIndex;
    Direction currentDirection;

    InputModifier *leftModifiers[2];
    InputModifier *upModifiers[1];
    InputModifier *rightModifiers[2];
    InputModifier *downModifiers[1];

    // Currently active input modifier (there's only one at a time)
    InputModifier *activeInputModifier;

    void removeDPadInputs(Gamecube_Data_t &data);

  public:
    InputHandler();
    void processInput(Gamecube_Data_t &data);
    void updateCurrentState(Gamecube_Report_t &report);
    bool directionReleased(uint8_t input, bool &dirPressed);
    void updateActiveInputModifier(Direction newDirection,
                                   InputModifier *modifiers[],
                                   const uint8_t &maxArraySize);
    InputModifier *getNextModifier(Direction newDirection,
                                   InputModifier *modifiers[],
                                   const uint8_t &maxArraySize);
};
#endif // GCTRAIN_INPUTHANDLER_HPP_