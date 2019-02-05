#ifndef GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_H_
#define GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_H_

#include "EscapeOption.hpp"
#include <Nintendo.h>

class NoEscapeOption : public EscapeOption {
  public:
    void inputEscapeOption(Gamecube_Data_t *dataToModify);
};

#endif // GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_H_
