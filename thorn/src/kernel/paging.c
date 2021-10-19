#include "kernel/paging.h"
#include "common/logging.h"

mm_table_t * get_page_table (unsigned short upper_attributes, unsigned short lower_attributes, bool is_block) {
    mm_table_t * page = (mm_table_t *) get_free_page ();
    if (page == 0) {
        LOG ("Out of memory! No page was returned!");
        while (1) {}
    }
    for (int i = 0; i < 512; i++) {
        mm_descriptor_t * desc = page->descriptors + i * sizeof (unsigned long);
        desc->valid            = 0;
        desc->block            = ! is_block;
        desc->lower_attributes = lower_attributes;
        desc->address          = 0;
        desc->upper_attributes = upper_attributes;
    }
    return page;
}

bool put_address (mm_descriptor_t * dest, mm_table_t * address) {
    // Check if address is 4 kB-aligned (i.e., 12 least significant bits are 0)
    if ((ptr_t) address & 0xFFF) {
        LOG ("ERROR: Table is not 4 kB-aligned!");
        printf ("  -> Page table address is %p\r\n", address);
        return false;
    }

    // Write address with trailing zeroes removed
    dest->address = (ptr_t) address >> 12;

    // Update valid flag
    dest->valid = true;
    return true;
}
