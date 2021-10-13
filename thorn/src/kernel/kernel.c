#include "common/logging.h"
#include "common/printf.h"
#include "common/utils.h"
<<<<<<< HEAD
#include "common/gpu.h"
#include "kernel/mm.h"
#include "kernel/timer.h"
=======
#include "kernel/fork.h"
>>>>>>> 436bff3 (WIP: try to generate different mmu data aborts)
#include "kernel/irq.h"
#include "kernel/mini_uart.h"
#include "kernel/mm.h"
#include "kernel/sched.h"
#include "kernel/sys.h"
<<<<<<< HEAD
#include "common/logging.h"
#include "common/rainbow.h"
=======
#include "kernel/timer.h"
>>>>>>> 436bff3 (WIP: try to generate different mmu data aborts)

void user_process1 (char * array) {
    if (* array == '1') {
        LOG ("EL0: Before data abort");
        printf ("Printing aborting data: %d\r\n", * (char *) 0x000000001234abcd);
        printf ("Printing aborting data: %d\r\n", * (char *) 0x00f0000200000000);

        // printf ("Printing aborting data: %d\r\n", * (char *) 0xffff00001234abcd);
        // printf ("Printing aborting data: %d\r\n", * (char *) 0x0000000600000000); // produces invalid_el0_64 error
        // printf ("Printing aborting data: %d\r\n", * (char *) 0x0000000800000000); // crashes raspberry
        // printf ("Printing aborting data: %d\r\n", * (char *) 0x123400000000abcd);
        // printf ("Printing aborting data: %d\r\n", * (char *) 0x000012340000abcd);
        // printf ("Printing aborting data: %d\r\n", * (char *) 0xffff12340000abcd);
        LOG("EL0: After data abort");
    }
    
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
    int err = call_sys_clone ((unsigned long) & user_process1,
                              (unsigned long) "12345", stack);
    if (err < 0) {
        printf ("Error while cloning process 1\n\r");
        return;
    }
    stack = call_sys_malloc ();
    if (stack < 0) {
        printf ("Error while allocating stack for process 2\n\r");
        return;
    }
    err = call_sys_clone ((unsigned long) & user_process1, (unsigned long) "abcd",
                          stack);
    if (err < 0) {
        printf ("Error while cloning process 2\n\r");
        return;
    }
    stack = call_sys_malloc ();
    if (stack < 0) {
        printf ("Error while allocating stack for process 3\n\r");
        return;
    }
    err = call_sys_clone ((unsigned long) & user_process1, (unsigned long) "+-*/",
                          stack);
    if (err < 0) {
        printf ("Error while cloning process 3\n\r");
        return;
    }
    call_sys_exit ();
}

void kernel_process () {
    printf ("Kernel process started. EL %d\r\n", get_el ());
    
    int err = move_to_user_mode ((unsigned long) & user_process);
    if (err < 0) {
        printf ("Error while moving process to user mode\n\r");
    }
}

void kernel_main (int processor_id) {
    
    static volatile unsigned int current_processor = 0;
    
    if (processor_id == 0) {
        uart_init ();
        init_printf (0, putc);
        irq_vector_init ();
        timer_init ();
        enable_interrupt_controller ();
        enable_irq ();
        task_init ();
        
        LOG("Logging works");
        
        printf ("Initialising Framebuffer...\r\n");
        int gpu_status = init_gpu ();
        if (!gpu_status) {
            printf ("Error while initialising Framebuffer\r\n");
        } else {
            color * fb = get_fb ();
            if (!fb) {
                printf ("Error: Invalid Framebuffer received\r\n");
            } else {
                printf ("Received framebuffer: %p\r\n", fb);
            }
        }
    }
    
    while (processor_id != current_processor);
    
    printf ("Hello, from processor %d\n\r", processor_id);
    
    current_processor++;
    
    if (processor_id == 0) {
        while (current_processor != 3);
        int res = copy_process (PF_KTHREAD, (unsigned long) & kernel_process, 0, 0);
        if (res < 0) {
            printf ("error while starting kernel process");
            return;
        }

       while (1) {
           schedule ();
       }
    }
    if (processor_id == 1) {
        while (current_processor != 3);
        draw();
    }
    
    while (1);
}
