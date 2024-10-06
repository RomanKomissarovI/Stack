#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>

#define DEBUG

#ifdef DEBUG
    #define DEBUG_PRINTF(...) printf(__VA_ARGS__)
    #define DEBUG_PR_ERR(err) {                                         \
        if (err != 0) {                                                 \
            PrintError(err, __FILE__, __LINE__, __PRETTY_FUNCTION__);   \
            return err;                                                 \
        }                                                               \
    }
    #define ON_DEBUG(...) __VA_ARGS__

    #define STACK_CTOR(stk) StackCtor(&stk, #stk, __FILE__, __LINE__)
    #define STACK_DUMP(stk) StackDump(stk, __FILE__, __LINE__)
#else
    #define DEBUG_PRINTF(...)
    #define DEBUG_PR_ERR(err) {                                         \
        if (err != 0) {                                                 \
            PrintError(err, __FILE__, __LINE__, __PRETTY_FUNCTION__);   \
            return err;                                                 \
        }                                                               \
    }
    #define ON_DEBUG(...)

    #define STACK_CTOR(stk) StackCtor(&stk)
    #define STACK_DUMP(stk) StackDump(stk)
#endif

#define Free(ptr) \
{                 \
    free(ptr);    \
    ptr = nullptr;\
}

#endif // MACROS_H