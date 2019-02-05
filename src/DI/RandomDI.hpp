#ifndef GCTRAIN_DI_RANDOMDI_H_
#define GCTRAIN_DI_RANDOMDI_H_

#include <Arduino.h>
#include <Nintendo.h>
#include "DI.hpp"
#include "../constants.hpp"

class RandomDI : public DI
{
    public:
        RandomDI();
        void inputDI(Gamecube_Data_t* dataToModify);
};

#endif // GCTRAIN_DI_RANDOMDI_H_