#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include "InputDiff.hpp"
#include "InputRecording.hpp"
#include "constants.hpp"
#include <Nintendo.h>
#ifdef DEBUG
#include "PrintReport.hpp"
#endif

class InputPlayback : public InputModifier {
  private:
    Gamecube_Data_t currentData;
    bool playingBack;
    uint16_t timeElapsed;
    unsigned long startTime;
    uint8_t currInputDiffIndex;
    InputDiffStore &inputDiffStore;

  public:
    explicit InputPlayback(InputDiffStore &inputDiffStore);
    void initialize();
    void modifyInput(Gamecube_Data_t &dataToModify);
    bool nextDiffExists();
    bool canApplyNextDiff();
    void applyNextDiff();
    void modifyWithCurrentData(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_