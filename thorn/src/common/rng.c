#include "common/rng.h"

void init_rng () {
    // Discard initial "not-so-random" numbers
    put32 (RNG_TOTAL_BIT_COUNT_THRESHOLD, RNG_INIT_DISCARD_COUNT);

    // Min FiFo count to generate interrupt
    put32 (RNG_FIFO_COUNT, 2 << RNG_FIFO_COUNT_RNG_FIFO_THRESHOLD__SHIFT);

    // Enable RNG, 1MHz sample rate
    put32 (RNG_CTRL, (3 << RNG_CTRL_RNG_DIV_CTRL__SHIFT | RNG_CTRL_RNG_RBGEN__MASK));

    // Ensure warmup period is over
    while (get32 (RNG_TOTAL_BIT_COUNT) <= 16) {}
    LOG ("Initialised RNG successfully");
}

unsigned int random () {
    // Check that FiFo is not empty
    while ((get32 (RNG_FIFO_COUNT) & RNG_FIFO_COUNT_RNG_FIFO_COUNT__MASK) == 0) {}

    // Read and return a random number
    return get32 (RNG_FIFO_DATA);
}
