#ifndef SASC_INPUTMODIFIERS_DI_SETSDI_HPP_
#define SASC_INPUTMODIFIERS_DI_SETSDI_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which simulates random SDI by mashing random DI, then
 * returns to neutral, then repeats.
 *
 */
class SetSDI : public InputModifier {
  private:
    enum class State : char { DIR_UNSET, NEUTRAL, DI };
    State nextState;
    uint8_t storedXAxis;
    uint8_t storedYAxis;

  public:
    SetSDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_SETSDI_HPP_