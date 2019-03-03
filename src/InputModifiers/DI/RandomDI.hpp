#ifndef SASC_INPUTMODIFIERS_DI_RANDOMDI_HPP_
#define SASC_INPUTMODIFIERS_DI_RANDOMDI_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which mashes random DI, then returns to neutral, then
 * repeats
 *
 */
class RandomDI : public InputModifier {
  private:
    enum class State : char { NEUTRAL, DI };
    State nextState;
    uint8_t currentWaitFrames;
    uint8_t storedXAxis;
    uint8_t storedYAxis;

  public:
    RandomDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_RANDOMDI_HPP_