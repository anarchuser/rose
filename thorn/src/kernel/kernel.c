#include "common/font.h"
#include "common/gpu.h"
#include "common/logging.h"
#include "common/printf.h"
#include "common/rainbow.h"
#include "common/screen.h"
#include "common/status_led.h"
#include "common/utils.h"
#include "kernel/fork.h"
#include "kernel/irq.h"
#include "kernel/mini_uart.h"
#include "kernel/mm.h"
#include "kernel/sched.h"
#include "kernel/sys.h"
#include "kernel/timer.h"

void user_process1 (char * array) {
    char buf[2] = {0};
    while (1) {
        for (int i = 0; i < 5; i++) {
            buf[0] = array[i];
            call_sys_write (buf);
            delay (100000);
        }
    }
}

void user_process () {
    char buf[30] = {0};
    tfp_sprintf (buf, "User process started\n\r");
    call_sys_write (buf);
    unsigned long stack = call_sys_malloc ();
    if (stack < 0) {
        printf ("Error while allocating stack for process 1\n\r");
        return;
    }
    int err = call_sys_clone ((unsigned long) &user_process1, (unsigned long) "12345", stack);
    if (err < 0) {
        printf ("Error while cloning process 1\n\r");
        return;
    }
    stack = call_sys_malloc ();
    if (stack < 0) {
        printf ("Error while allocating stack for process 1\n\r");
        return;
    }
    err = call_sys_clone ((unsigned long) &user_process1, (unsigned long) "abcd", stack);
    if (err < 0) {
        printf ("Error while cloning process 2\n\r");
        return;
    }
    call_sys_exit ();
}

void kernel_process () {
    // printf ("Kernel process started. EL %d\r\n", get_el ());
    int err = move_to_user_mode ((unsigned long) &user_process);
    if (err < 0) {
        printf ("Error while moving process to user mode\n\r");
    }
}

void kernel_init (void) {
    uart_init ();
    init_printf (0, putc);
    irq_vector_init ();
    timer_init ();
    enable_interrupt_controller ();
    enable_irq ();
    task_init ();

    // Turn status led OFF and power led ON
    set_led (0, STATUS_LED);
    set_led (0, POWER_LED);

    printf ("Initialising Framebuffer...\r\n");
    int gpu_status = init_gpu ();
    if (!gpu_status) {
        printf ("Error while initialising Framebuffer\r\n");
    } else {
        if (!get_fb ()) {
            printf ("Error: Invalid Framebuffer received\r\n");
        } else {
            font_set_normal ();
            init_printf (0, putc_screen);
            printf ("Frame  buffer:     %p\r\n", get_fb ());
            printf ("Width  resolution: %d\r\n", get_fb_info ()->virtual_width);
            printf ("Height resolution: %d\r\n", get_fb_info ()->virtual_height);
        }
    }

    printf ("|...|...|...|...|\r\n");
    printf ("|\t|\t|\t|\t|\r\n");

    LOG ("Initialisation done");
    ERROR ("I'm important!");
}


void kernel_main (int processor_id) {

    static volatile unsigned int current_processor = 0;
    if (processor_id == 0) {
        kernel_init ();
    }

    // Synchronisation to prevent concurrent print
    while (processor_id != current_processor) {}
    printf ("Hello, from processor %d in EL %d\n\r", processor_id, get_el ());
    current_processor++;
    while (current_processor != 4) {}

    switch (processor_id) {
        case 0: {
            // int res = copy_process (PF_KTHREAD, (unsigned long) &kernel_process, 0, 0);
            // if (res < 0) {
            //     // printf ("error while starting kernel process");
            //     return;
            // }
            while (1) {
                // schedule ();
            }
            break;
        }
        case 1:
            if (get_fb ()) {
                color_t white_color  = {0xff, 0xff, 0xff, 0xff};
                color_t blue_color   = {0xff, 0x00, 0x00, 0xff};
                color_t green_color  = {0x00, 0xff, 0x00, 0xff};
                color_t purple_color = {0xff, 0x00, 0xff, 0xff};

                // random lines
                drawline (POINT (1, 400),
                          POINT (600, 1),
                          blue_color);
                drawline (POINT (1, 400),
                          POINT (600, 900),
                          blue_color);
                drawline (POINT (600, 900),
                          POINT (600, 1),
                          blue_color);
                drawline (POINT (600, 1),
                          POINT (1, 400),
                          green_color);
                drawline (POINT (3, 3),
                          POINT (20, 800),
                          green_color);
                drawline (POINT (1200, 900),
                          POINT (1, 904),
                          purple_color);
                drawline (POINT (1, 500),
                          POINT (900, 600),
                          white_color);
                drawline (POINT (20, 60),
                          POINT (60, 90),
                          purple_color);

                // grid lines
                drawline (POINT (20, 80),
                          POINT (20, 500),
                          white_color);
                drawline (POINT (20, 80),
                          POINT (800, 80),
                          white_color);
                drawline (POINT (800, 500),
                          POINT (800, 80),
                          white_color);
                drawline (POINT (800, 500),
                          POINT (20, 500),
                          white_color);

                // rectangle
                drawrec (POINT (300, 300),
                         POINT (400, 400),
                         purple_color);

                drawcircle (POINT (1200, 500),
                            100,
                            purple_color);
            }
            break;
        case 2:
        case 3:
        default:
            while (1)
                ;
            printf ("Undefined behaviour on processor %d\r\n", processor_id);
    }
    // printf ("Processor %d going out of scope\r\n", processor_id);
}
