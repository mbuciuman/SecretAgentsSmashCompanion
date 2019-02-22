#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include "InputDiff.hpp"
#include "InputRecording.hpp"
#include <Nintendo.h>
#include <linked_list.h>

class InputPlayback : public InputModifier {
  private:
    Gamecube_Data_t initialData;
    bool playingBack;
    unsigned long timeElapsed;
    InputRecording *inputRecording;
    Iterator<InputDiff> *itDiff;

  public:
    explicit InputPlayback(InputRecording *inputRecording);
    ~InputPlayback();
    void initialize(Gamecube_Data_t &initialData);
    void modifyInput(Gamecube_Data_t &dataToModify);
    bool canApplyNextDiff();
    void applyNextDiff(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTPLAYBACK_HPP_