#include "common/debug.h"

void print_hex (unsigned char dec) {
    char fst = dec / 16;
    char snd = dec % 16;
    fst = (fst > 9) ? 'A' + fst - 10 : '0' + fst;
    snd = (snd > 9) ? 'A' + snd - 10 : '0' + snd;
    printf ("%c%c ", fst, snd);
}

void hex_dump (byte_t * array) {
    for (int i = 0; i < * (unsigned int *) array;) {
        i += 4;
        for (int j = 1; j <= 4; j++) {
            print_hex (array[i - j]);
        }
        printf (" ");
        if (!(i % 32)) printf ("\r\n");
    }
    printf ("\r\n");
}

void int_dump (unsigned int * array) {
    for (int i = 0; i < * array; i++) {
        printf ("%d ", array[i]);
    }
    printf ("\r\n");
}
