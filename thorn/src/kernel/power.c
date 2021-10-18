#include "kernel/power.h"

void poweroff (unsigned int timeout, bool block) {
}

void reboot (unsigned int timeout, bool block) {
    unsigned int pm_rstc, pm_wdog;

    /* Setup watchdog for reset */
    pm_rstc = get32 (PM_RSTC);
    // watchdog timer = timer clock / 16; need password (31:16) + value (11:0)
    pm_wdog = PM_PASSWORD | (timeout & PM_WDOG_TIME_SET);
    pm_rstc = PM_PASSWORD | (pm_rstc & PM_RSTC_WRCFG_CLR) | PM_RSTC_WRCFG_FULL_RESET;
    put32 (PM_WDOG, pm_wdog);
    put32 (PM_RSTC, pm_rstc);

    while (block)
        ;
}
