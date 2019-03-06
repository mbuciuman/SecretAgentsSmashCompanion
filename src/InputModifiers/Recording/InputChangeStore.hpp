#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTCHANGESTORE_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTCHANGESTORE_HPP_

#include "Constants.hpp"
#include "InputChange.hpp"
#include <Nintendo.h>

/**
 * @brief Class for storing changes between controller inputs
 *
 */
class InputChangeStore {
  private:
    // controller data at start recording
    Gamecube_Data_t initialData;
    // array for storing input changes and their times
    InputChange inputChanges[MAX_STORE_SIZE];
    // counter for stored input changes
    uint8_t totalChanges;
    // time between last input change and end of recording
    uint16_t lastTime;

  public:
    InputChangeStore();
    void initialize(const Gamecube_Data_t &initialData);
    bool canStoreChange();
    void storeChange(const uint16_t timeDiff,
                     const Gamecube_Report_t &firstReport,
                     const Gamecube_Report_t &secondReport);
    void storeLastTime(const uint16_t lastTime);
    InputChange &getInputChange(const int index);
    uint8_t getTotalChanges();
    uint16_t getLastTime();
    Gamecube_Data_t getInitialData();
    void reset();
};
#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTCHANGESTORE_HPP_
