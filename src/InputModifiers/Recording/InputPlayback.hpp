#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include "InputDiff.hpp"
#include "InputRecording.hpp"
#include <Nintendo.h>

class InputPlayback : public InputModifier {
  private:
    Gamecube_Data_t initialData;
    bool playingBack;
    uint16_t timeElapsed;
    uint8_t currInputDiff;
    InputDiffStore &inputDiffStore;

  public:
    explicit InputPlayback(InputDiffStore &inputDiffStore);
    void initialize(Gamecube_Data_t &initialData);
    void modifyInput(Gamecube_Data_t &dataToModify);
    bool canApplyNextDiff();
    void applyNextDiff(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_