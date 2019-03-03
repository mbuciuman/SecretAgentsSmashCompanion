#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_

#include "../InputModifier.hpp"
#include "InputDiffStore.hpp"
#include "constants.hpp"
#include <Nintendo.h>
#ifdef DEBUG
#include "PrintReport.hpp"
#endif

class InputRecording : public InputModifier {
  private:
    Gamecube_Data_t previousData;
    uint16_t timeElapsed;
    unsigned long previousTime;
    bool recording;
    InputDiffStore inputDiffStore;

  public:
    explicit InputRecording();
    void startRecording(Gamecube_Data_t &initialData);
    void modifyInput(Gamecube_Data_t &currentData);
    bool currentDataEqualsPrevious(Gamecube_Data_t &currentData);
    void createNewDiff(Gamecube_Data_t &currentData);
    void cleanUp();
    InputDiffStore &getInputDiffStore();
};
#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_