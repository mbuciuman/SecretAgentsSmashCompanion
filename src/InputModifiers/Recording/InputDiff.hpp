#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_

#include "../../constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>

// maximum number of consecutive input changes at a time (17 total possible)
static const uint8_t MAX_CONS_INPUTS = 8;

struct SingleInputDiff {
    ControllerInput input;
    int16_t valueDiff;
};

class InputDiff {
  private:
    uint16_t timeDiff;
    SingleInputDiff singleDiffs[MAX_CONS_INPUTS];
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
};

#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_