#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_

#include "../InputModifier.hpp"
#include "Constants.hpp"
#include "InputChangeStore.hpp"
#include <Nintendo.h>
#ifdef DEBUG
#include "Utility.hpp"
#endif

/**
 * @brief Handles recording input and storing to an InputChangeStore object
 *
 */
class InputRecording : public InputModifier {
  private:
    // the input data at the time when an input change was stored
    Gamecube_Data_t previousData;
    // the amount of time elapsed between stored input changes
    uint16_t timeElapsed;
    // the previous time in ms when an input change was stored
    unsigned long previousTime;
    // boolean flag representing if actively recording
    bool recording;
    // object for storing input changes
    InputChangeStore &inputChangeStore;

  public:
    explicit InputRecording(InputChangeStore &inputChangeStore);
    void startRecording(const Gamecube_Data_t &initialData);
    void modifyInput(Gamecube_Data_t &currentData);
    bool currentDataEqualsPrevious(const Gamecube_Data_t &currentData);
    void storeNewChange(const Gamecube_Data_t &currentData);
    void cleanUp();
    InputChangeStore &getInputChangeStore();
};
#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTRECORDING_HPP_