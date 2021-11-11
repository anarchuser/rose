#ifndef _ROSE_C_TEMPERATURE_H
#define _ROSE_C_TEMPERATURE_H

#include "common/font.h"
#include "common/screen.h"
#include "common/stdbool.h"
#include "kernel/fork.h"
#include "kernel/gpio.h"
#include "kernel/mailbox.h"

#define GPIO_FAN 18

// Temperature the system tries to keep. Turns off cooling if it falls below.
// NOTE: The pi hits a 'soft' limit at 70 °C, reducing clock frequency.
//       This value is defined in the config.txt and defaults to 60 °C if not set
#define TEMPERATURE_FAN_OFF 47500
#define TEMPERATURE_FAN_ON  50000
#define TEMPERATURE_MAX     80000

#define TEMPERATURE_CHECK_DELAY 2000

#define TEMPERATURE_POINTS 200

#define TEMPERATURE_GRAPH_LOW  45000
#define TEMPERATURE_GRAPH_HIGH 55000

static volatile unsigned int __attribute__ ((aligned (16))) temperature_request[8];

static unsigned int temperatures[TEMPERATURE_POINTS] = {0};
static unsigned int current_temperature_index        = 0;

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

void draw_temp_graph (void);

#endif//_ROSE_C_TEMPERATURE_H