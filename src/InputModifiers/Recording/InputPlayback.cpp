#include "InputPlayback.hpp"

InputPlayback::InputPlayback(InputDiffStore &inputDiffStore)
    : initialData(Gamecube_Data_t()), playingBack(false), timeElapsed(0),
      currInputDiff(0), inputDiffStore(inputDiffStore) {}

void InputPlayback::initialize(Gamecube_Data_t &initialData) {
    this->initialData = initialData;
    timeElapsed = 0;
    currInputDiff = 0;
}

void InputPlayback::modifyInput(Gamecube_Data_t &dataToModify) {
    Serial.println(F("ip_mi"));
    if (!playingBack) {
        initialize(dataToModify);
    } else if (canApplyNextDiff()) {
        applyNextDiff(dataToModify);
    } else {
        playingBack = false;
    }
}

bool InputPlayback::canApplyNextDiff() {
    return currInputDiff < inputDiffStore.getTotalDiffs() - 1;
}

void InputPlayback::applyNextDiff(Gamecube_Data_t &dataToModify) {
    inputDiffStore.getDiff(currInputDiff).applyTo(dataToModify);
    InputDiff nextDiff = inputDiffStore.getDiff(currInputDiff + 1);
    timeElapsed -= nextDiff.getTimeDiff();
    currInputDiff++;
}

void InputPlayback::cleanUp() { playingBack = false; }