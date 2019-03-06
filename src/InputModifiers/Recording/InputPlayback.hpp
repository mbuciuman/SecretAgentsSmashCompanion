#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include "Constants.hpp"
#include "InputChange.hpp"
#include "InputRecording.hpp"
#include <Nintendo.h>
#ifdef DEBUG
#include "Utility.hpp"
#endif

/**
 * @brief Handles playing-back stored input from an InputChangeStore object
 *
 */
class InputPlayback : public InputModifier {
  private:
    // representation of controller data at time of recording
    Gamecube_Data_t currentData;
    // boolean flag representing whether actively playing back
    bool playingBack;
    // total time elapsed between previous Input Change application
    uint16_t timeElapsed;
    // millis at time of previous Input Change application
    unsigned long startTime;
    // index of the current Input Change within the Input Change store
    uint8_t currInputChangeIndex;
    // object representing storage of Input Changes over time
    InputChangeStore &inputChangeStore;

  public:
    explicit InputPlayback(InputChangeStore &inputChangeStore);
    void startPlayback();
    void modifyInput(Gamecube_Data_t &dataToModify);
    bool nextChangeExists();
    bool canApplyNextChange();
    void applyNextChange();
    void modifyWithCurrentData(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_