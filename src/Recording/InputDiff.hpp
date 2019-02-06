#ifndef GCTRAIN_RECORDING_INPUTDIFF_HPP_
#define GCTRAIN_RECORDING_INPUTDIFF_HPP_

#include "../constants.hpp"
#include <Arduino.h>
#include <Nintendo.h>
#include <linked_list.h>

struct SingleInputDiff {
    ControllerInput input;
    int8_t valueDiff;
};

class InputDiff {
    private:
        long timeDiff;
        LinkedList<SingleInputDiff> *inputDiffs; 
        LinkedList<SingleInputDiff>* createDiffs(Gamecube_Data_t *firstData, Gamecube_Data_t *secondData);

    public:
        InputDiff(long timeDiff, Gamecube_Data_t *firstData, Gamecube_Data_t *secondData);
};

#endif // GCTRAIN_RECORDING_INPUTDIFF_HPP_