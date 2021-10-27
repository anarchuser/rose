#ifndef _ROSE_K_P_RNG_H
#define _ROSE_K_P_RNG_H

#include "kernel/peripherals/base.h"

#define RNG_BASE                      (PBASE + 0x104000)
#define RNG_CTRL                      (RNG_BASE + 0x00)
#define RNG_TOTAL_BIT_COUNT           (RNG_BASE + 0x0C)
#define RNG_TOTAL_BIT_COUNT_THRESHOLD (RNG_BASE + 0x10)
#define RNG_FIFO_DATA                 (RNG_BASE + 0x20)
#define RNG_FIFO_COUNT                (RNG_BASE + 0x24)

#define RNG_CTRL_RNG_RBGEN__MASK                 0x1FFF
#define RNG_CTRL_RNG_DIV_CTRL__SHIFT             13
#define RNG_FIFO_COUNT_RNG_FIFO_COUNT__MASK      0xFF
#define RNG_FIFO_COUNT_RNG_FIFO_THRESHOLD__SHIFT 8

#endif//_ROSE_K_P_RNG_H
