#include "InputModifier.hpp"

/**
 * @brief Times how many wait frames are remaining (useful as a mini-semaphore
 * for state changing)
 *
 * @return true still frames left to wait
 * @return false no wait frames left
 */
bool InputModifier::waitRemaining() {
    if (currentWaitFrames < WAIT_FRAMES) {
        currentWaitFrames++;
        return true;
    }
    currentWaitFrames = 0;
    return false;
}