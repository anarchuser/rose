#include "common/rng.h"

void init_rng () {
    put32 (RNG_STATUS, RNG_INIT_DISCARD_COUNT);
    put32 (RNG_STATUS, 1);
    put32 (RNG_CTRL, 0x01);
}

unsigned int random () {
    while (get32 (RNG_STATUS) >> 24 == 0) {}
    return get32 (RNG_DATA);
}
