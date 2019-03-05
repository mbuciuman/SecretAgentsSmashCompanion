#ifndef SASC_INPUTMODIFIERS_DI_SETDI_HPP_
#define SASC_INPUTMODIFIERS_DI_SETDI_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which mashes DI in the direction set on initialization
 */
class SetDI : public InputModifier {
  private:
    boolean directionSet;
    uint8_t storedXAxis;
    uint8_t storedYAxis;

  public:
    SetDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_SETDI_HPP_