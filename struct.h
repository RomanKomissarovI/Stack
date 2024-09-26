#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>

typedef int stack_type;
enum StackErrors {
    No_Errors = 0,
    Error_Size = 2,
    Error_Capacity = 3,
    Null_Ptr = 4,
    Null_Data_Ptr = 5,
};

struct Stack
{
    stack_type* data;
    int size;
    int capacity;
};

#endif // STRUCT_H