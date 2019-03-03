#ifndef GCTRAIN_INPUTMODIFIERS_ESCAPEOPTION_MASHJUMP_HPP_
#define GCTRAIN_INPUTMODIFIERS_ESCAPEOPTION_MASHJUMP_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

class MashJump : public InputModifier {
  private:
    enum class State : char { NEUTRAL, JUMP };
    State nextState;

  public:
    explicit MashJump();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_INPUTMODIFIERS_ESCAPEOPTION_MASHJUMP_HPP_