#include "common/font.h"
#include "common/gpu.h"
#include "common/logging.h"
#include "common/printf.h"
#include "common/rainbow.h"
#include "common/rng.h"
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

void user_process_rng () {
    char buf[2] = {0};
    while (1) {
        buf[0] = random ();
        call_sys_write (buf);
        delay (100000);
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
        printf ("Error while allocating stack for process 2\n\r");
        return;
    }
    err = call_sys_clone ((unsigned long) &user_process1, (unsigned long) "abcd", stack);
    if (err < 0) {
        printf ("Error while cloning process 2\n\r");
        return;
    }
    stack = call_sys_malloc ();
    if (stack < 0) {
        printf ("Error while allocating stack for process 3\n\r");
        return;
    }
    err = call_sys_clone ((unsigned long) &user_process_rng, 0, stack);
    if (err < 0) {
        printf ("Error while cloning process 3\n\r");
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
    init_rng ();

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
            int res = copy_process (PF_KTHREAD, (unsigned long) &kernel_process, 0, 0);
            if (res < 0) {
                ERROR ("Can't start kernel process");
                break;
            }
            while (1) {
                schedule ();
            }
            break;
        }
        case 1:
            if (get_fb ()) {
                test_drawing ();
            }
            break;
        case 2:
        case 3:
            break;
        default:
            while (1)
                ;
            printf ("Undefined behaviour on processor %d\r\n", processor_id);
    }
    printf ("Processor %d going out of scope\r\n", processor_id);
}
