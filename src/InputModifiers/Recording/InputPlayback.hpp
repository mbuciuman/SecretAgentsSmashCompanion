#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include "Constants.hpp"
#include "InputDiff.hpp"
#include "InputRecording.hpp"
#include <Nintendo.h>
#ifdef DEBUG
#include "PrintReport.hpp"
#endif

/**
 * @brief Handles playing-back stored input from an InputDiffStore object
 *
 */
class InputPlayback : public InputModifier {
  private:
    // representation of controller data at time of recording
    Gamecube_Data_t currentData;
    // boolean flag representing whether actively playing back
    bool playingBack;
    // total time elapsed between previous input diff application
    uint16_t timeElapsed;
    // millis at time of previous input diff application
    unsigned long startTime;
    // index of the current input diff within the input diff store
    uint8_t currInputDiffIndex;
    // object representing storage of input diffs over time
    InputDiffStore &inputDiffStore;

  public:
    explicit InputPlayback(InputDiffStore &inputDiffStore);
    void startPlayback();
    void modifyInput(Gamecube_Data_t &dataToModify);
    bool nextDiffExists();
    bool canApplyNextDiff();
    void applyNextDiff();
    void modifyWithCurrentData(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_