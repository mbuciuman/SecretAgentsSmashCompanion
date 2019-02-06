#ifndef GCTRAIN_RECORDING_INPUTPLAYBACK_HPP_
#define GCTRAIN_RECORDING_INPUTPLAYBACK_HPP_

import "../InputModifier.hpp"

class InputPlayback : public InputModifier {
    public:
        void modifyInput(Gamecube_Data_t *dataToModify);
        void cleanUp();
}

#endif // GCTRAIN_RECORDING_INPUTPLAYBACK_HPP_