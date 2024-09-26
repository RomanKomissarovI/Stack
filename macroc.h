#ifndef MACROS_H
#define MACROS_H

void Free(void* ptr);
#ifdef DEBUG
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...)
#endif

#include <stdlib.h>
#include "color_print.h"

#define DEBUG_PR(err_code) ColorPrint(RedColor, "line{%d}m func{%s} file{%s} Error IncrStackSize: code %d\n", __LINE__, __PRETTY_FUNCTION__, __FILE__, err)

void Free(void* ptr)
{
    free(ptr);
    ptr = nullptr;
}

#endif // MACROS_H