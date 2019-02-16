#ifndef GCTRAIN_RECORDING_NOINPUTPLAYBACK_HPP_
#define GCTRAIN_RECORDING_NOINPUTPLAYBACK_HPP_

#include "../InputModifier.hpp"
#include <Nintendo.h>

class NoInputPlayback : public InputModifier {
  public:
    ~NoInputPlayback();
    void modifyInput(Gamecube_Data_t *dataToModify);
    void cleanUp();
};

#endif // GCTRAIN_RECORDING_NOINPUTPLAYBACK_HPP_