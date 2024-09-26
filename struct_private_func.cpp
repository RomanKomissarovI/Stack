#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "struct_private_func.h"
#include "color_print.h"

int StackError(Stack* stk)
{
    StackNull(stk);

    if (stk->data == nullptr)
    {
        return Fail_Calloc;
    }

    if ((stk->size > stk->capacity) || (stk->size < 0) || (stk->capacity < 0))
    {
        return Error_Size;
    }
    
    return No_Errors;
}

void StackNull(Stack* stk)
{
    if (stk == nullptr)
    {
        ColorPrint(RedColor, "Error: null-stack_ptr\n");
        assert(nullptr);
    }
}

void StackDump(Stack* stk)
{
    StackNull(stk);

    ColorPrint(RedColor, "Elems:\n"); 

    int err = StackError(stk);
    int i = 0;
    int size = (stk->size < stk->capacity) ? stk->size : stk->capacity;

    while (i < size)
    {
        ColorPrint(RedColor, "%d ", stk->data[i]);
        ++i;
        if (i % 20 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");

    ColorPrint(RedColor, "size: %d\ncapacity: %d\nError code: %d\n", stk->size, stk->capacity, err);
}

void Recalloc(Stack* stk, int old_size, int new_capacity)
{
    StackNull(stk);

    stk->data = (stack_type*) realloc(stk->data, new_capacity * sizeof(stack_type));
    
    StackAssert(stk);

    memset(stk->data + old_size, 0, (new_capacity - old_size) * sizeof(stack_type));
}

void StackAssert(Stack* stk)
{
    StackNull(stk);

    if (StackError(stk))
    {
        StackDump(stk);
        assert(0);
    }
}

void IncrStackSize(Stack* stk)
{
    StackNull(stk);

    if (stk->size == stk->capacity)
    {
        stk->capacity = (int) stk->capacity * 1.4 + 10;
        Recalloc(stk, stk->size, stk->capacity);
    }

    (stk->size)++;
}

void DecrStackSize(Stack* stk)
{
    StackNull(stk);

    (stk->size)--;

    if (stk->size <= stk->capacity / 2.5 - 5)
    {
        Recalloc(stk, stk->size, stk->capacity / 2);
        stk->capacity /= 2;
    }

    StackAssert(stk);
}
