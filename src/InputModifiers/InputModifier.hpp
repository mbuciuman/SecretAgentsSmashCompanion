#ifndef GCTRAIN_INPUTMODIFIERS_INPUTMODIFIER_HPP_
#define GCTRAIN_INPUTMODIFIERS_INPUTMODIFIER_HPP_

#include "constants.hpp"
#include <Nintendo.h>

class InputModifier {
  public:
    virtual void modifyInput(Gamecube_Data_t &dataToModify) = 0;
    virtual void cleanUp() = 0;
};
#endif // GCTRAIN_INPUTMODIFIERS_INPUTMODIFIER_HPP_