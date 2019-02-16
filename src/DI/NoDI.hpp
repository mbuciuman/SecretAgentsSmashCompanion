#ifndef GCTRAIN_DI_NODI_HPP_
#define GCTRAIN_DI_NODI_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

class NoDI : public InputModifier {
  public:
    void modifyInput(Gamecube_Data_t &dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_DI_NODI_HPP_
