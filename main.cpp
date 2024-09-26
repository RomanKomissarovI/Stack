#include <stdio.h>
#include "struct_public_func.h"

int main()
{
    Stack a;
    StackCtor(&a);
    for(int i = 0; i < 1000; ++i)
    {
        StackPush(&a, i + 1);
    }
    StackDump(&a);
    printf("\n\n");

    for(int i = 0; i < 900; ++i)
    {
        StackPop(&a);
    }
    StackDump(&a);

    printf("\nTROLOLOLOLO LOLOLO LOLOLO EEE\n");
    return 0;
}