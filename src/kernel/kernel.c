#include "kernel/mini_uart.h"
#include "common/printf.h"
#include "common/utils.h"
#include "kernel/mm.h"
#include "kernel/timer.h"
#include "kernel/irq.h"
#include "kernel/sched.h"
#include "kernel/fork.h"
#include "kernel/sys.h"
#include "kernel/user.h"


void kernel_process () {
    printf ("Kernel process started. EL %d\r\n", get_el ());
    unsigned long begin = (unsigned long) & user_begin;
    unsigned long end = (unsigned long) & user_end;
    unsigned long process = (unsigned long) & user_process;
    int err = move_to_user_mode (begin, end - begin, process - begin);
    if (err < 0) {
        printf ("Error while moving process to user mode\n\r");
    }
}


void kernel_main (int processor_id) {
    
    static unsigned int current_processor = 0;
    
    if (processor_id == current_processor) {
        uart_init ();
        init_printf (0, putc);
        irq_vector_init ();
        timer_init ();
        enable_interrupt_controller ();
        enable_irq ();
        task_init ();
    }
    
    while (processor_id != current_processor);
    
    printf ("Hello, from processor %d\n\r", processor_id);
    
    current_processor ++;
    
    if (processor_id == 0) {
        while (current_processor != 4);
        int res = copy_process (PF_KTHREAD, (unsigned long) & kernel_process, 0);
        if (res < 0) {
            printf ("error while starting kernel process");
            return;
        }
        
        while (1) {
            schedule ();
        }
    }
}
