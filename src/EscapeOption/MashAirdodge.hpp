#ifndef GCTRAIN_ESCAPEOPTION_MASHAIRDODGE_HPP_
#define GCTRAIN_ESCAPEOPTION_MASHAIRDODGE_HPP_

#include "../constants.hpp"
#include "../InputModifier.hpp"
#include <Nintendo.h>

class MashAirdodge : public InputModifier {
  private:
    bool executingAirdodge;

  public:
    MashAirdodge();
    void modifyInput(Gamecube_Data_t *dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_ESCAPEOPTION_MASHAIRDODGE_HPP_