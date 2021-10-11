#include "kernel/mm.h"

static unsigned short mem_map[PAGING_PAGES] = {0,};

ptr_t get_free_page () {
    for (int i = 0; i < PAGING_PAGES; i ++) {
        if (mem_map[i] == 0) {
            mem_map[i] = 1;
            return LOW_MEMORY + i * PAGE_SIZE;
        }
    }
    return 0;
}

void free_page (ptr_t p) {
    mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}

// void memzero (ptr_t src, ptr_t n) {
//     if (n == 0) return;
//     *(byte_t *) src = 0;
//     memzero(src + 1, n - 1);
// }

// void memcpy (ptr_t des, ptr_t src, ptr_t n) {
//     if (n == 0) return;
//     *(byte_t *) des = (byte_t *) src;
//     memcpy(des + 1, src + 1, n - 1);
// }