#include <stdio.h>
#include <stdlib.h>
#include "stack_func.h"

int main()
{
    Stack a;

    int err = No_Errors;
    if (!err) err = STACK_CTOR(a);

    for(int i = 0; i < 1000; ++i)
    {
        if (!err) err = StackPush(&a, i + 1);
    }
    err = STACK_DUMP(&a);

    for(int i = 0; i < 960; ++i)
    {
        if (!err) err = StackPop(&a);
    }
    STACK_DUMP(&a);

    StackDtor(&a);

    return 0;
}