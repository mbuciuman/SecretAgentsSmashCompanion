#ifndef GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_HPP_
#define GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

class NoEscapeOption : public InputModifier {
  public:
    void modifyInput(Gamecube_Data_t *dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_HPP_
