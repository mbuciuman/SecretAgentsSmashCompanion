#ifndef GCTRAIN_ESCAPEOPTION_MASHAIRDODGE_H_
#define GCTRAIN_ESCAPEOPTION_MASHAIRDODGE_H_

#include "../constants.hpp"
#include "EscapeOption.hpp"
#include <Nintendo.h>

class MashAirdodge : public EscapeOption {
  private:
    bool executingAirdodge;

  public:
    MashAirdodge();
    void inputEscapeOption(Gamecube_Data_t *dataToModify);
};

#endif // GCTRAIN_ESCAPEOPTION_MASHAIRDODGE_H_