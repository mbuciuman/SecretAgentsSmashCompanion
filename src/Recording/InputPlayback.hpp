#ifndef GCTRAIN_RECORDING_INPUTPLAYBACK_HPP_
#define GCTRAIN_RECORDING_INPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include "InputDiff.hpp"
#include <Nintendo.h>
#include <linked_list.h>

class InputPlayback : public InputModifier {
  private:
    Gamecube_Data_t initialData;
    LinkedList<InputDiff> *inputDiffs;

  public:
    explicit InputPlayback();
    ~InputPlayback();
    void initialize(Gamecube_Data_t &initialData,
                    LinkedList<InputDiff> *inputDiffs);
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_RECORDING_INPUTPLAYBACK_HPP_