#ifndef GCTRAIN_RECORDING_INPUTRECORDING_H_
#define GCTRAIN_RECORDING_INPUTRECORDING_H_

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
        void playbackRecording(Gamecube_Data_t *dataToModify);

};
#endif // GCTRAIN_RECORDING_INPUTRECORDING_H_