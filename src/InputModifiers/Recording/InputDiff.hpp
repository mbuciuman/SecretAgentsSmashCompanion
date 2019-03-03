#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_

#include "../../Constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Struct representing the diff of a single input.
 * NOTE: due to struct byte padding, this is 6 bytes.
 *
 * Math:
 * ControllerInput: 1 byte == sizeof(uint8_t)
 * valueDiff: 2 bytes == sizeof(int16_t)
 * Struct padding (determined by compiling): 3 bytes
 */
struct SingleInputDiff {
    ControllerInput input;
    int16_t valueDiff;
};

/**
 * @brief Object representing the diff (difference) between controller inputs
 * over a given elapsed time.
 *
 */
class InputDiff {
  private:
    // time elapsed between controller input changes in ms.
    uint16_t timeDiff;
    // array where all individual button diffs are stored
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

#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTDIFF_HPP_