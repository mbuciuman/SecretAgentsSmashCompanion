#ifndef GCTRAIN_DI_LEFTRIGHTDI_H_
#define GCTRAIN_DI_LEFTRIGHTDI_H_

#include "../constants.hpp"
#include "DI.hpp"
#include <Arduino.h>
#include <Nintendo.h>

class LeftRightDI : public DI {
      private:
        Direction prevDirection;

      public:
        LeftRightDI();
        void inputDI(Gamecube_Data_t *dataToModify);
};

#endif // GCTRAIN_DI_LEFTRIGHTDI_H_