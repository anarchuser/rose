#include "common/gpu.h"
#include "common/logging.h"
#include "common/printf.h"
#include "common/rainbow.h"
#include "common/screen.h"
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

    printf ("Initialising Framebuffer...\r\n");
    int gpu_status = init_gpu ();
    if (! gpu_status) {
        printf ("Error while initialising Framebuffer\r\n");
    } else {
        color_t * fb = get_fb ();
        if (! fb) {
            printf ("Error: Invalid Framebuffer received\r\n");
        } else {
            printf ("Received framebuffer: %p\r\n", fb);
        }
    }

    LOG ("Initialisation done");

    printf ("MAX_WIDTH: %d\n\r", get_fb_info ()->virtual_width);
    printf ("MAX_HEIGHT: %d\n\r", get_fb_info ()->virtual_height);

    printf ("GET_MAX_WIDTH: %d\n\r", get_max_width ());
    printf ("GET_MAX_HEIGHT: %d\n\r", get_max_height ());

    printf ("PITCH: %d\n\r", get_fb_info ()->pitch);
}


void kernel_main (int processor_id) {

    static volatile unsigned int current_processor = 0;
    if (processor_id == 0) {
        kernel_init ();
    }

    while (processor_id != current_processor)
        ;

    // printf ("Hello, from processor %d\n\r", processor_id);

    current_processor++;
    while (current_processor != 3)
        ;
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
        }
        case 1:
            if (get_fb ()) {
                color_t white_color  = {0xff, 0xff, 0xff, 0xff};
                color_t blue_color   = {0xff, 0x00, 0x00, 0xff};
                color_t green_color  = {0x00, 0xff, 0x00, 0xff};
                color_t purple_color = {0xff, 0x00, 0xff, 0xff};
                // random lines
                drawline (1, 400, 600, 1, blue_color);
                drawline (1, 400, 600, 900, blue_color);
                drawline (600, 900, 600, 1, blue_color);
                drawline (600, 1, 1, 400, green_color);
                drawline (3, 3, 20, 800, green_color);
                drawline (1200, 900, 1, 904, purple_color);
                drawline (1, 500, 900, 600, white_color);

                // grid
                drawline (20, 80, 20, 500, white_color);
                drawline (20, 80, 800, 80, white_color);

                // rectangle
                drawrec (300, 300, 400, 400, purple_color);
            }
            break;
        case 2:
        case 3:
        default:
            // printf ("Undefined behaviour on processor %d\r\n", processor_id);
            while (1)
                ;
    }
    // printf ("Processor %d going out of scope\r\n", processor_id);
}
