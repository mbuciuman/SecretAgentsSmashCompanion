#ifndef SASC_INPUTMODIFIERS_DI_RANDOMDI_HPP_
#define SASC_INPUTMODIFIERS_DI_RANDOMDI_HPP_

#include "../InputModifier.hpp"
#include "Utility.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Input modifier which mashes random DI by moving the control stick in a
 * random direction every frame
 */
class RandomDI : public InputModifier {
  private:
    uint8_t storedXAxis;
    uint8_t storedYAxis;

  public:
    RandomDI();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_DI_RANDOMDI_HPP_