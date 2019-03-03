#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_

#include "../InputModifier.hpp"
#include "Constants.hpp"
#include "InputDiffStore.hpp"
#include <Nintendo.h>
#ifdef DEBUG
#include "PrintReport.hpp"
#endif

/**
 * @brief Handles recording input and storing to an InputDiffStore object
 *
 */
class InputRecording : public InputModifier {
  private:
    // the input data at the time when an input diff was stored
    Gamecube_Data_t previousData;
    // the amount of time elapsed between stored input diffs
    uint16_t timeElapsed;
    // the previous time in ms when an input diff was stored
    unsigned long previousTime;
    // boolean flag representing if actively recording
    bool recording;
    // object for storing input diffs
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
#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_