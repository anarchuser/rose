#ifndef _ROSE_K_POWER_H
#define _ROSE_K_POWER_H

#include "common/stdbool.h"
#include "common/utils.h"
#include "kernel/peripherals/power.h"

// power off (timeout / 16 in seconds?)
void poweroff (unsigned int timeout, bool block);

// reboot (timeout / 16 in seconds?)
void reboot (unsigned int timeout, bool block);

#endif//_ROSE_K_POWER_H