#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

typedef int stack_type;
enum StackErrors {
    No_Errors = 0,
    Fail_Calloc = 1,
    Error_Size = 2,
};

struct Stack
{
    stack_type* data;
    int size;
    int capacity;
};

#endif // STRUCT_H