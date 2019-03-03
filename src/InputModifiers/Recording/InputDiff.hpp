#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_

#include "../../constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>

struct SingleInputDiff {
    ControllerInput input;
    int16_t valueDiff;
};

class InputDiff {
  private:
    uint16_t timeDiff;
    SingleInputDiff singleDiffs[MAX_SINGLE_INPUT_DIFFS];
    void storeDiffs(Gamecube_Report_t &firstReport,
                    Gamecube_Report_t &secondReport);
    void storeSingleDiff(uint8_t firstVal, uint8_t secondVal,
                         ControllerInput input);

  public:
    explicit InputDiff();
    uint16_t getTimeDiff();
    void initialize(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                    Gamecube_Report_t &secondReport);
    void applyTo(Gamecube_Data_t &dataToModify);
    void applySingleDiffTo(SingleInputDiff &singleInputDiff,
                           Gamecube_Data_t &dataToModify);
    bool inputsDiffer(uint8_t first, uint8_t second, ControllerInput input);
    void reset();
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_