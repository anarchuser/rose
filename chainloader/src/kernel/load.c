#include "kernel/load.h"

void print_hex (unsigned char dec) {
    \
    char first = dec / 16;                                              \
    char second = dec % 16;                                             \
    first = (first > 9) ? 'A' + first - 10 : '0' + first;               \
    second = (second > 9) ? 'A' + second - 10 : '0' + second;           \
    printf ("%c%c ", first, second);                                    \

}

void receive_kernel (void) {
    char * const kernel_load_address = (char *) LOAD_ADDRESS;
    char * const kernel_size_address = kernel_load_address - sizeof (int);
    
    uart_send_string ("Wait for kernel & kernel size...\r\n");
    for (int i = sizeof (int); i > 0;) { // 4 is size of int
        kernel_size_address[--i] = uart_recv ();
    }
    
    int length = * (int *) kernel_size_address;
    printf ("Write %d bytes into %p\r\n", length, kernel_load_address);
    
    /** IMPORTANT **/
    /// FROM HERE ONWARDS, CHAIN LOADER OVERWRITES ITSELF. NO FURTHER NORMAL FUNCTION CALLS POSSIBLE! ///
    for (int i = 0; i < length; i++) {
        while (!((* (unsigned int *) AUX_MU_LSR_REG) & 0x01));
        kernel_load_address[i] = (* (unsigned int *) AUX_MU_IO_REG) & 0xFF;
    }
    
    * (unsigned int *) AUX_MU_IO_REG = '!';

//    (swap + CHAINLOAD_OFFSET) ();
    ((void (*) ()) LOAD_ADDRESS) ();
//    while (1);
}
