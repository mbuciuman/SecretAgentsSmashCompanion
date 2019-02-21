#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_

#include "../../constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <linked_list.h>

struct SingleInputDiff {
    ControllerInput input;
    int8_t valueDiff;
    ~SingleInputDiff() {}
};

class InputDiff {
  private:
    long timeDiff;
    LinkedList<SingleInputDiff> *inputDiffs;
    static LinkedList<SingleInputDiff> *
    createDiffs(Gamecube_Data_t &firstData, Gamecube_Data_t &secondData);

  public:
    explicit InputDiff(long timeDiff, Gamecube_Data_t &firstData,
                       Gamecube_Data_t &secondData);
    ~InputDiff();
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_