#ifndef _ROSE_K_P_RNG_H
#define _ROSE_K_P_RNG_H

#include "kernel/peripherals/base.h"

#define RNG_BASE        (PBASE + 0x104000)
#define RNG_CTRL        (RNG_BASE + 0x00)
#define RNG_STATUS      (RNG_BASE + 0x04)
#define RNG_DATA        (RNG_BASE + 0x08)

#endif //_ROSE_K_P_RNG_H
