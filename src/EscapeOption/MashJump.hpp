#ifndef GCTRAIN_ESCAPEOPTION_MASHJUMP_HPP_
#define GCTRAIN_ESCAPEOPTION_MASHJUMP_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

class MashJump : public InputModifier {
  private:
    bool executingJump;

  public:
    explicit MashJump();
    ~MashJump();
    void modifyInput(Gamecube_Data_t *dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_ESCAPEOPTION_MASHJUMP_HPP_