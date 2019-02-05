#ifndef GCTRAIN_DI_NODI_H_
#define GCTRAIN_DI_NODI_H_

#include "DI.hpp"
#include <Nintendo.h>

class NoDI : public DI {
  public:
    void inputDI(Gamecube_Data_t *dataToModify);
};

#endif // GCTRAIN_DI_NODI_H_
