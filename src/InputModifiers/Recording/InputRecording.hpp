#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_

#include "../InputModifier.hpp"
#include "InputDiffStore.hpp"
#include <Nintendo.h>

class InputRecording : public InputModifier {
  private:
    Gamecube_Data_t initialData;
    Gamecube_Data_t previousData;
    Gamecube_Data_t currentData;
    uint16_t previousTime;
    bool recording;
    InputDiffStore inputDiffStore;

  public:
    explicit InputRecording();
    void startRecording(Gamecube_Data_t initialData);
    void modifyInput(Gamecube_Data_t &currentData);
    bool currentDataEqualsPrevious();
    void createNewDiff();
#ifdef DEBUG
    void printReport(Gamecube_Report_t &report);
#endif
    void cleanUp();
    InputDiffStore &getInputDiffStore();
};
#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_