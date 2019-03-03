#ifndef SASC_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_
#define SASC_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

class LeftRightDI : public InputModifier {
  private:
    bool movingRight;
    Direction nextDirection;
    uint8_t currentWaitFrames;

  public:
    LeftRightDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_LEFTRIGHTDI_HPP_