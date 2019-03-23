#ifndef SASC_INPUTMODIFIERS_OOSOPTIONS_NAIROOS_HPP_
#define SASC_INPUTMODIFIERS_OOSOPTIONS_NAIROOS_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which waits with shield up (L pressed) until it detects
 * a hit on it (rumble activated), then inputs N-Air
 */
class NairOOS : public InputModifier {
  private:
    enum class State : char { SHIELD, NAIR };
    State nextState;

  public:
    NairOOS();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_OOSOPTIONS_NAIROOS_HPP_