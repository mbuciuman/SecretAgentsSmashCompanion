#ifndef SASC_INPUTMODIFIERS_OOSOPTIONS_GRABOOS_HPP_
#define SASC_INPUTMODIFIERS_OOSOPTIONS_GRABOOS_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which waits with shield up (L pressed) until it detects
 * a hit on it (rumble activated), then inputs a grab
 */
class GrabOOS : public InputModifier {
  private:
    enum class State : char { SHIELD, GRAB };
    State nextState;

  public:
    GrabOOS();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_OOSOPTIONS_GRABOOS_HPP_