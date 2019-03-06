#ifndef SASC_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_
#define SASC_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

class LeftRightDI : public InputModifier {
  private:
    enum class State { LEFT, RIGHT };
    State nextState;

  public:
    LeftRightDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_