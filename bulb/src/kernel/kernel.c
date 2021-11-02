#include "common/font.h"
#include "common/gpu.h"
#include "common/logging.h"
#include "common/printf.h"
#include "common/status_led.h"
#include "common/utils.h"
#include "kernel/mm.h"
#include "kernel/mmu.h"

void hang (int led, int cycles) {
    while (1) {
        toggle_led (led);
        delay (cycles);
    }
}

void kernel_init (void) {
    set_led (0, POWER_LED);
    set_led (0, STATUS_LED);

    if (init_gpu ()) {
        if (get_fb ()) {
            font_set_normal ();
            init_printf (0, putc_screen);
            printf ("Frame  buffer:     %p\r\n", get_fb ());
            printf ("Width  resolution: %d\r\n", get_fb_info ()->virtual_width);
            printf ("Height resolution: %d\r\n", get_fb_info ()->virtual_height);

            LOG ("Initialisation done");
            ERROR ("I'm important!");
        } else
            hang (POWER_LED, 1000000);
    } else
        hang (POWER_LED, 2000000);
}

void kernel_main (int processor_id) {
    kernel_init ();

    init_mmu ();

    printf ("Hello, from processor %d in EL %d\r\n", processor_id, get_el ());

    hang (STATUS_LED, 5000000);
}
