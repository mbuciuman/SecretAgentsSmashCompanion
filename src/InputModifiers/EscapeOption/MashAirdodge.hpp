#ifndef SASC_INPUTMODIFIERS_ESCAPEOPTION_MASHAIRDODGE_HPP_
#define SASC_INPUTMODIFIERS_ESCAPEOPTION_MASHAIRDODGE_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

class MashAirdodge : public InputModifier {
  private:
    enum class State : char { NEUTRAL, AIRDODGE };
    State nextState;
    uint8_t storedXAxis;
    uint8_t storedYAxis;

  public:
    explicit MashAirdodge();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_ESCAPEOPTION_MASHAIRDODGE_HPP_