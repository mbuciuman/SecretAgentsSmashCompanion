#ifndef GCTRAIN_DI_DI_H_
#define GCTRAIN_DI_DI_H_

#include <Nintendo.h>

class DI {
  public:
    virtual void inputDI(Gamecube_Data_t *dataToModify) = 0;
};
#endif // GCTRAIN_DI_DI_H_