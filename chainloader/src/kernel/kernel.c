#include "kernel/kernel.h"

void kernel () {
    uart_init ();
    uart_send_string ("\033[2J\033[0;0H"); // clear screen
    uart_send_string ("Booting chainloader...");

    // Copy chainloader to offset
    char * const old = (char *) LOAD_ADDRESS;
    char * const new = (char *) LOAD_ADDRESS + CHAINLOAD_OFFSET;
    for (unsigned int i = 0; i < LOADER_SIZE; i++) {
        new[i] = old[i];
    }

    // Receive and execute kernel from serial
    (receive_kernel + CHAINLOAD_OFFSET) ();
}
