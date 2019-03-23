#ifndef SASC_INPUTMODIFIERS_OOSOPTIONS_UPBOOS_HPP_
#define SASC_INPUTMODIFIERS_OOSOPTIONS_UPBOOS_HPP_

#include "../InputModifier.hpp"
#include <Arduino.h>
#include <Nintendo.h>

/**
 * @brief Input modifier which waits with shield up (L pressed) until it detects
 * a hit on it (rumble activated), then inputs an Up-B
 */
class UpBOOS : public InputModifier {
  private:
    enum class State : char { SHIELD, UP_B };
    State nextState;

  public:
    UpBOOS();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // SASC_INPUTMODIFIERS_OOSOPTIONS_UPSMASHOOS_HPP_