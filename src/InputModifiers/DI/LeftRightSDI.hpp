#ifndef SASC_INPUTMODIFIERS_DI_LEFTRIGHTSDI_HPP_
#define SASC_INPUTMODIFIERS_DI_LEFTRIGHTSDI_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which simulates SDI by mashing left/right DI, then
 * returning the stick to neutral.
 *
 */
class LeftRightSDI : public InputModifier {
  private:
    bool movingRight;
    Direction nextDirection;

  public:
    LeftRightSDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_LEFTRIGHTSDI_HPP_