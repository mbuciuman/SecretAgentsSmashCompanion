#ifndef SASC_INPUTMODIFIERS_ESCAPEOPTION_MASHJUMP_HPP_
#define SASC_INPUTMODIFIERS_ESCAPEOPTION_MASHJUMP_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

/**
 * @brief Input modifier which mashes the jump button
 */
class MashJump : public InputModifier {
  private:
    enum class State : char { NEUTRAL, JUMP };
    State nextState;

  public:
    explicit MashJump();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_ESCAPEOPTION_MASHJUMP_HPP_