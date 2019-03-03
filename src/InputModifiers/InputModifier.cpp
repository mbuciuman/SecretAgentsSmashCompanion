#include "InputModifier.hpp"

bool InputModifier::waitRemaining() {
    if (currentWaitFrames < WAIT_FRAMES) {
        currentWaitFrames++;
        return true;
    }
    currentWaitFrames = 0;
    return false;
}