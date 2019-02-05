#ifndef GCTRAIN_DI_RANDOMDI_H_
#define GCTRAIN_DI_RANDOMDI_H_

#include "../constants.hpp"
#include "DI.hpp"
#include <Arduino.h>
#include <Nintendo.h>

class RandomDI : public DI {
  public:
    void inputDI(Gamecube_Data_t *dataToModify);
};

#endif // GCTRAIN_DI_RANDOMDI_H_