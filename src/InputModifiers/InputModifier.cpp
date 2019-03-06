#include "InputModifier.hpp"

/**
 * @brief Times how many cycles to wait are remaining (useful as a
 * mini-semaphore for state changing)
 *
 * @return true cycles still left to wait
 * @return false no wait cycles left
 */
bool InputModifier::waitRemaining() {
    if (currentWaitCycles < WAIT_CYCLES) {
        currentWaitCycles++;
        return true;
    }
    currentWaitCycles = 0;
    return false;
}