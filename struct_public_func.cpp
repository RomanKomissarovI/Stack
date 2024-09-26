#include <assert.h>
#include <stdlib.h>
#include "struct_public_func.h"
//#include "struct_private_func.h"
#include "color_print.h"
#include "macroc.h"

void StackPush(Stack* stk, stack_type a)
{
    IncrStackSize(stk);

    stk->data[stk->size - 1] = a;
}

void StackPop(Stack* stk)
{
    DecrStackSize(stk);

    stk->data[stk->size] = 0;
}

void StackCtor(Stack* stk)
{
    StackNull(stk);

    stk->size = 0;
    stk->capacity = 10;
    stk->data = (stack_type*) calloc(stk->capacity, sizeof(stack_type));

    StackAssert(stk);
}

void StackDtor(Stack* stk)
{
    StackNull(stk);

    Free(stk->data);
}