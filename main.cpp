#include <stdio.h>
#include "struct_public_func.h"

int main()
{
    Stack a;
    int err = No_Errors;
    if (!err) err = StackCtor(&a);
    for(int i = 0; i < 1000; ++i)
    {
        if (!err) err = StackPush(&a, i + 1);
    }
    if (!err) err = StackDump(&a);
    printf("\n\n");

    for(int i = 0; i < 900; ++i)
    {
        if (!err) err = StackPop(&a);
    }
    StackDump(&a);

    printf("\nTROLOLOLOLO LOLOLO LOLOLO EEE\n");
    return 0;
}