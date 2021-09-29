#ifndef _ROSE_C_LOGGING_H
#define _ROSE_C_LOGGING_H

#include "common/printf.h"

#define LOG(msg)        do {                        \
    printf(__FILE__":%d: %s\r\n", __LINE__, msg);   \
} while (0)

#define ASSERT(expr)    do {                        \
    if (! (expr)) LOG("Assertion failed");          \
} while (0)


#endif /*_ROSE_C_LOGGING_H*/
