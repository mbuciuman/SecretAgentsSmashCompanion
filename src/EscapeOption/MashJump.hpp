#ifndef GCTRAIN_ESCAPEOPTION_MASHJUMP_H_
#define GCTRAIN_ESCAPEOPTION_MASHJUMP_H_

#include "EscapeOption.hpp"
#include <Nintendo.h>

class MashJump : public EscapeOption {
  private:
    bool executingJump;

  public:
    MashJump();
    void inputEscapeOption(Gamecube_Data_t *dataToModify);
};

#endif // GCTRAIN_ESCAPEOPTION_MASHJUMP_H_