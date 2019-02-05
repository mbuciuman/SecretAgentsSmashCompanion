#ifndef GCTRAIN_DI_NODI_H_
#define GCTRAIN_DI_NODI_H_

#include <Nintendo.h>
#include "DI.hpp"

class NoDI : public DI
{
    public:
        void inputDI(Gamecube_Data_t* dataToModify);
};

#endif // GCTRAIN_DI_NODI_H_
