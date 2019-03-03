#ifndef SASC_INPUTMODIFIERS_INPUTMODIFIER_HPP_
#define SASC_INPUTMODIFIERS_INPUTMODIFIER_HPP_

#include "Constants.hpp"
#include <Nintendo.h>

/**
 * @brief Parent abstract class for any input modifier. Requires children to
 * have modification and clean-up logic implementations
 */
class InputModifier {
  protected:
    uint8_t currentWaitFrames = 0;
    bool waitRemaining();

  public:
    virtual void modifyInput(Gamecube_Data_t &dataToModify) = 0;
    virtual void cleanUp() = 0;
};
#endif // SASC_INPUTMODIFIERS_INPUTMODIFIER_HPP_