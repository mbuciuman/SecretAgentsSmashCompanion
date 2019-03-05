#ifndef SASC_INPUTMODIFIERS_RECORDING_INPUTCHANGE_HPP_
#define SASC_INPUTMODIFIERS_RECORDING_INPUTCHANGE_HPP_

#include "../../Constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>

#ifdef _MSC_VER
#pragma pack(push, 1)
typedef struct {
#else
typedef struct __attribute__((packed)) {
#endif
    struct {
        uint8_t a : 1;
        uint8_t b : 1;
        uint8_t x : 1;
        uint8_t y : 1;
        uint8_t l : 1;
        uint8_t r : 1;
        uint8_t z : 1;
        uint8_t spare : 1;
    };
    uint8_t lAnalog;
    uint8_t rAnalog;
    uint8_t xAxis;
    uint8_t yAxis;
    uint8_t cxAxis;
    uint8_t cyAxis;
} SerializedController;
#ifdef _MSC_VER
#pragma pack(pop)
#endif

/**
 * @brief Object representing the change in controller inputs over a given
 * elapsed time.
 */
class InputChange {
  private:
    // time elapsed between controller input changes in ms.
    uint16_t timeDiff;
    SerializedController controller;
    void storeChanges(Gamecube_Report_t &firstReport,
                      Gamecube_Report_t &secondReport);

  public:
    explicit InputChange();
    uint16_t getTimeDiff();
    void initialize(uint16_t timeDiff, Gamecube_Report_t &firstReport,
                    Gamecube_Report_t &secondReport);
    void applyTo(Gamecube_Data_t &dataToModify);
};

#endif // SASC_INPUTMODIFIERS_RECORDING_INPUTCHANGE_HPP_