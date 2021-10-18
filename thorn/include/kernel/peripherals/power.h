#ifndef _ROSE_K_P_POWER_H
#define _ROSE_K_P_POWER_H

#include "kernel/peripherals/base.h"

#define PM_BASE PBASE + 0x100000

#define PM_RSTC PM_BASE + 0x1c
#define PM_WDOG PM_BASE + 0x24

#define PM_WDOG_RESET 0000000000
#define PM_PASSWORD 0x5a000000
#define PM_WDOG_TIME_SET 0x000fffff
#define PM_RSTC_WRCFG_CLR 0xffffffcf
#define PM_RSTC_WRCFG_SET 0x00000030
#define PM_RSTC_WRCFG_FULL_RESET 0x00000020
#define PM_RSTC_RESET 0x00000102

#endif//_ROSE_K_P_POWER_H

/* Copyright (C) 2020 Aaron Alef */