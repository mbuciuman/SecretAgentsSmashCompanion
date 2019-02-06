#ifndef GCTRAIN_DI_RANDOMDI_HPP_
#define GCTRAIN_DI_RANDOMDI_HPP_

#include "../constants.hpp"
#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

class RandomDI : public InputModifier {
  public:
    void modifyInput(Gamecube_Data_t *dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_DI_RANDOMDI_HPP_