#ifndef GCTRAIN_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_
#define GCTRAIN_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_

#include "../../constants.hpp"
#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

class LeftRightDI : public InputModifier {
  private:
    Direction prevDirection;

  public:
    LeftRightDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_