#ifndef SASC_INPUTMODIFIERS_NOMODIFIER_HPP_
#define SASC_INPUTMODIFIERS_NOMODIFIER_HPP_

#include "Constants.hpp"
#include "InputModifier.hpp"

/**
 * @brief Input modifier which just performs a no-op
 *
 */
class NoModifier : public InputModifier {
  public:
    explicit NoModifier();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};
#endif // SASC_INPUTMODIFIERS_NOMODIFIER_HPP_