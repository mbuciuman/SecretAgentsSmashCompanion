#ifndef GCTRAIN_RECORDING_INPUTRECORDING_HPP_
#define GCTRAIN_RECORDING_INPUTRECORDING_HPP_

#include <Nintendo.h>
#include <linked_list.h>
#include "InputDiff.hpp"

class InputRecording {
    private:
        Gamecube_Data_t *initialData;
        Gamecube_Data_t *currentData;
        LinkedList<InputDiff> *inputDiffs;

    public:
        InputRecording(Gamecube_Data_t *initialData);
        void submitInput(Gamecube_Data_t *currentData);
        void stopRecording();

};
#endif // GCTRAIN_RECORDING_INPUTRECORDING_HPP_