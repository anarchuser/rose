#ifndef _ROSE_C_RNG_H
#define _ROSE_C_RNG_H

// Implementation based on Circle OS:
// github.com/rsta2/circle

// Initial numbers are less random, so discard this many:
#define RNG_INIT_DISCARD_COUNT      0x1000

#include "kernel/peripherals/rng.h"
#include "common/utils.h"

#include "common/status_led.h"

void init_rng (void);

unsigned int random (void);


#endif //_ROSE_C_RNG_H
