#ifndef GCTRAIN_ESCAPEOPTION_ESCAPEOPTION_H_
#define GCTRAIN_ESCAPEOPTION_ESCAPEOPTION_H_

#include <Nintendo.h>

class EscapeOption {
  public:
    virtual void inputEscapeOption(Gamecube_Data_t *dataToModify) = 0;
};

#endif // GCTRAIN_ESCAPEOPTION_ESCAPEOPTION_H_