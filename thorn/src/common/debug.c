#include "common/debug.h"

void print_hex (unsigned char dec) {
    char fst = dec / 16;
    char snd = dec % 16;
    fst = (fst > 9) ? 'A' + fst - 10 : '0' + fst;
    snd = (snd > 9) ? 'A' + snd - 10 : '0' + snd;
    printf ("%c%c ", fst, snd);
}

void byte_dump (unsigned int size, byte_t * array) {
    for (int i = 0; i < size; i ++) {
        print_hex (array[i]);
        if (! ((i + 1) % 4)) printf (" ");
        if (! ((i + 1) % 80)) printf ("\r\n");
    }
    printf ("\r\n");
}

void int_dump (unsigned int size, unsigned int * array) {
    for (int i = 0; i < size / sizeof (int); i ++) {
        printf ("%d\t", array[i]);
    }
    printf ("\r\n");
}
