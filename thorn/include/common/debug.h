#ifndef _ROSE_C_DEBUG_H
#define _ROSE_DEBUG_H

#include "common/stddef.h"
#include "common/printf.h"
#include "common/logging.h"

#define CHECKPOINT LOG ("Checkpoint");

void print_hex (unsigned char dec);

void hex_dump (byte_t * array);

void int_dump (unsigned int * array);

#endif //_ROSE_C_DEBUG_H