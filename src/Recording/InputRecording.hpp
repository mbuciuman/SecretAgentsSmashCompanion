#ifndef GCTRAIN_RECORDING_INPUTRECORDING_HPP_
#define GCTRAIN_RECORDING_INPUTRECORDING_HPP_

#include "../InputModifier.hpp"
#include "InputDiff.hpp"
#include <Nintendo.h>
#include <linked_list.h>

class InputRecording : public InputModifier {
  private:
    Gamecube_Data_t initialData;
    Gamecube_Data_t currentData;
    LinkedList<InputDiff> *inputDiffs;

  public:
    explicit InputRecording();
    ~InputRecording();
    void startRecording(Gamecube_Data_t &initialData);
    void modifyInput(Gamecube_Data_t &currentData);
    void cleanUp();
    LinkedList<InputDiff> *getInputDiffs();
};
#endif // GCTRAIN_RECORDING_INPUTRECORDING_HPP_