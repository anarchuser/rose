#include "kernel/paging.h"

mm_table_t * get_page_table (unsigned short upper_attributes, unsigned short lower_attributes, bool is_block) {
    mm_table_t * page = (mm_table_t *) get_free_page ();
    for (int i = 0; i < 512; i ++) {
        mm_descriptor_t * desc = page->descriptor + i * sizeof (unsigned long);
        desc->valid = 0;
        desc->block = ! is_block;
        desc->lower_attributes = lower_attributes;
        desc->address = 0;
        desc->upper_attributes = upper_attributes;
    }
    return page;
}