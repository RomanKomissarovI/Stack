#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include "macros.h"

typedef int stack_t;
typedef unsigned long long canar_t;
ON_DEBUG(const canar_t k_Canar = 0xBADC0FFEE;)

enum StackErrors {
    No_Errors = 0,
    Error_Canar = 1,
    Error_Size = 2,
    Error_Capacity = 3,
    Null_Ptr = 4,
    Null_Data_Ptr = 5,
};

struct Stack
{
    ON_DEBUG(const char* name;)
    ON_DEBUG(const char* file;)
    ON_DEBUG(int line;)

    char* data;
    int size;
    int capacity;
};

#endif // STACK_H