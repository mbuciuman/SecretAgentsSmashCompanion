#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTDIFFSTORE_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTDIFFSTORE_HPP_

#include "InputDiff.hpp"
#include "constants.hpp"
#include <Nintendo.h>

/**
 * @brief Class for storing diffs (differences) between controller inputs
 *
 */
class InputDiffStore {
  private:
    // controller data at start of diffs
    Gamecube_Data_t initialData;
    // array for storing input diffs and their times
    InputDiff inputDiffs[MAX_STORE_SIZE];
    // counter for stored input diffs
    uint8_t totalDiffs;
    // time between last diff and end of recording
    uint16_t lastTime;

  public:
    InputDiffStore();
    void initialize(Gamecube_Data_t &initialData);
    bool canStoreDiff();
    void storeDiff(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                   Gamecube_Report_t &secondReport);
    void storeLastTime(uint16_t lastTime);
    InputDiff &getDiff(int index);
    uint8_t getTotalDiffs();
    uint16_t getLastTime();
    Gamecube_Data_t getInitialData();
    void reset();
};
#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTDIFFSTORE_HPP_
