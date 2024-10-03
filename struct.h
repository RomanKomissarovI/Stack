#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include "macros.h"

typedef int stack_type;
ON_DEBUG(const unsigned long long Canar = 0xBADC0FFEE;)

enum StackErrors {
    No_Errors = 0,
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

    stack_type* data;
    int size;
    int capacity;
};

#endif // STRUCT_H