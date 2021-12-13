#ifndef _ROSE_K_ETHERNET_H
#define _ROSE_K_ETHERNET_H

#include "common/logging.h"
#include "common/printf.h"
#include "common/stddef.h"
#include "common/utils.h"
#include "kernel/peripherals/ethernet.h"

void handle_ethernet_irq ();
bool init_ethernet ();

#endif /*_ROSE_K_ETHERNET_H */
