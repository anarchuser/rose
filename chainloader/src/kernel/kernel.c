#include "kernel/kernel.h"

void kernel () {
    uart_init ();
    init_printf (0, putc);
//    uart_send_string ("\033[2J\033[0;0H"); // clear screen
    uart_send_string ("\r\n");
    uart_send_string ("Booting "__FILE__"\r\n");
    
    relocate ();
    
    printf ("Old receive: %p\r\nNew receive: %p\r\n", receive_kernel, receive_kernel + CHAINLOAD_OFFSET);
    
    (receive_kernel + CHAINLOAD_OFFSET) ();
}

void relocate () {
    char * const old = (char *) LOAD_ADDRESS;
    char * const new = (char *) LOAD_ADDRESS + CHAINLOAD_OFFSET; // 0x80000 - 4096
    printf ("Copying %d bytes to %p...", LOADER_SIZE, new);
    for (unsigned int i = 0; i < LOADER_SIZE; i++) {
        new[i] = old[i];
    }
    uart_send_string ("Done\r\n");
}