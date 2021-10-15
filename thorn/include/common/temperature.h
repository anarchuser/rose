#ifndef _ROSE_C_TEMPERATURE_H
#define _ROSE_C_TEMPERATURE_H

#include "common/stdbool.h"
#include "kernel/mailbox.h"
#include "kernel/peripherals/gpio.h"

#define GPIO_FAN 18

// Temperature the system tries to keep. Turns off cooling if it falls below.
// NOTE: The pi hits a 'soft' limit at 70 °C, reducing clock frequency.
//       This value is defined in the config.txt and defaults to 60 °C if not set
#define TEMPERATURE_SHOULD  (50 * 1000)
#define TEMPERATURE_MAX     (80 * 1000)

#define TEMPERATURE_CHECK_DELAY 20000000

static volatile unsigned int __attribute__((aligned(16))) temperature_request[8];

// Max temperature in degree milliCelsius.
// USB + Ethernet are designed up to 70 °C but unlikely to overheat.
// CPU is designed up to 85 °C so 80 is probably a reasonable upper limit.
// Consider reducing to 70 °C if the workload on the ports increases
static int max_temperature;

bool init_temperature (void);

void regulate_temperature (void);

int get_max_temperature (void);

int get_temperature (void);

void set_fan (bool enable);

#endif //_ROSE_C_TEMPERATURE_H