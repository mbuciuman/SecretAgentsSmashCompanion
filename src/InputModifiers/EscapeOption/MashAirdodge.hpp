#ifndef GCTRAIN_INPUTMODIFIERS_ESCAPEOPTION_MASHAIRDODGE_HPP_
#define GCTRAIN_INPUTMODIFIERS_ESCAPEOPTION_MASHAIRDODGE_HPP_

#include "../../constants.hpp"
#include "../InputModifier.hpp"
#include <Nintendo.h>

class MashAirdodge : public InputModifier {
  private:
    bool executingAirdodge;

  public:
    explicit MashAirdodge();
    ~MashAirdodge();
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_INPUTMODIFIERS_ESCAPEOPTION_MASHAIRDODGE_HPP_