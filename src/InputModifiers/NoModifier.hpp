#ifndef GCTRAIN_INPUTMODIFIERS_NOMODIFIER_HPP_
#define GCTRAIN_INPUTMODIFIERS_NOMODIFIER_HPP_

#include "InputModifier.hpp"

class NoModifier : public InputModifier {
  public:
    explicit NoModifier();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};
#endif // GCTRAIN_INPUTMODIFIERS_NOMODIFIER_HPP_