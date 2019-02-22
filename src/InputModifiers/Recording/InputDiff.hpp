#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_

#include "../../constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <linked_list.h>

struct SingleInputDiff {
    ControllerInput input;
    int16_t valueDiff;
    ~SingleInputDiff() {}
};

class InputDiff {
  private:
    unsigned long timeDiff;
    LinkedList<SingleInputDiff> *singleDiffs;
    void initialize(Gamecube_Report_t &firstReport,
                    Gamecube_Report_t &secondReport);
    void addDiffIfDifferent(uint8_t firstVal, uint8_t secondVal,
                            ControllerInput input);

  public:
    explicit InputDiff(long timeDiff, Gamecube_Report_t &firstReport,
                       Gamecube_Report_t &secondReport);
    unsigned long getTimeDiff();
    void applyDiff(Gamecube_Data_t &dataToModify);
    void applySingleDiff(SingleInputDiff *singleDiff,
                         Gamecube_Data_t &dataToModify);
    ~InputDiff();
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_