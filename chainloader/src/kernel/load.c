#include "kernel/load.h"

//void print_hex (unsigned char dec) {
//    char first = dec / 16;
//    char second = dec % 16;
//    first = (first > 9) ? 'A' + first - 10 : '0' + first;
//    second = (second > 9) ? 'A' + second - 10 : '0' + second;
//    printf ("%c%c ", first, second);
//}

void receive_kernel (void) {
    char * const kernel_load_address = (char *) LOAD_ADDRESS;
    char * const kernel_size_address = kernel_load_address - sizeof (int);

    uart_send_string ("Ready to receive\r\n");
    for (int i = sizeof (int); i > 0;) {// 4 is size of int
        kernel_size_address[--i] = uart_recv ();
    }
    int length = *(int *) kernel_size_address;

    /** IMPORTANT **/
    /// FROM HERE ONWARDS, CHAIN LOADER OVERWRITES ITSELF. NO FURTHER NORMAL FUNCTION CALLS POSSIBLE! ///
    for (int i = 0; i < length; i++) {
        UART_RECEIVE (kernel_load_address[i]);
    }

    // Restore system registers
    asm("mov x0, x20");
    asm("mov x1, x21");
    asm("mov x2, x22");
    asm("mov x3, x23");

    ((void (*) ()) LOAD_ADDRESS) ();
}
