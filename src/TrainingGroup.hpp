#ifndef SASC_TRAININGGROUP_HPP_
#define SASC_TRAININGGROUP_HPP_

#include "InputModifiers/InputModifier.hpp"
#include <Nintendo.h>

extern bool checkDITrainingInput(Gamecube_Data_t &input, bool &buttonPressed);
extern bool checkEOTrainingInput(Gamecube_Data_t &input, bool &buttonPressed);
extern bool checkOOSTrainingInput(Gamecube_Data_t &input, bool &buttonPressed);
extern bool checkRecordingTrainingInput(Gamecube_Data_t &input,
                                        bool &buttonPressed);
extern bool checkPlaybackTrainingInput(Gamecube_Data_t &input,
                                       bool &buttonPressed);

typedef bool (*ValidationFunc)(Gamecube_Data_t &, bool &);
class TrainingGroup {
  private:
    ValidationFunc validationFunc;
    InputModifier **modifiers;
    uint8_t currentModifier;
    uint8_t modifiersSize;
    bool inputPressed;

  public:
    TrainingGroup(ValidationFunc f, InputModifier **modifiers,
                  uint8_t modifiersSize);
    bool checkInputToActivate(Gamecube_Data_t &input);
    bool hasNextModifier();
    InputModifier *getNextModifier();
    void resetModifiers();
};

#endif // SASC_TRAININGMODE_HPP_