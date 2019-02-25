#ifndef GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFFSTORE_HPP_
#define GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFFSTORE_HPP_

#include "InputDiff.hpp"
#include <Nintendo.h>

static const uint8_t MAX_STORE_SIZE = 28;

class InputDiffStore {
  private:
    InputDiff inputDiffs[MAX_STORE_SIZE];
    uint8_t totalDiffs;

  public:
    InputDiffStore();
    bool canStoreDiff();
    void storeDiff(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                   Gamecube_Report_t &secondReport);
    InputDiff &getDiff(int index);
    uint8_t getTotalDiffs();
    void reset();
};
#endif // GCTRAIN_INPUTMODIFIERS_RECORDING_INPUTDIFFSTORE_HPP_
