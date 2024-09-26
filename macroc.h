#ifdef DEBUG
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
    #define DEBUG_PRINTF(...)
#endif

#include <stdlib.h>

void Free(void* ptr)
{
    free(ptr);
    ptr = nullptr;
}
