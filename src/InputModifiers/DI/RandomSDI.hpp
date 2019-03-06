#ifndef SASC_INPUTMODIFIERS_DI_RANDOMSDI_HPP_
#define SASC_INPUTMODIFIERS_DI_RANDOMSDI_HPP_

#include "../InputModifier.hpp"
#include "Utility.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Input modifier which simulates random SDI by mashing random DI, then
 * returns to neutral, then repeats.
 */
class RandomSDI : public InputModifier {
  private:
    enum class State : char { NEUTRAL, DI };
    State nextState;
    uint8_t storedXAxis;
    uint8_t storedYAxis;

  public:
    RandomSDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_RANDOMSDI_HPP_