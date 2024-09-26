#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "struct_private_func.h"
#include "color_print.h"
//#include "macroc.h"

int StackError(Stack* stk)
{
    if (stk == nullptr)
    {
        ColorPrint(RedColor, "Error StackError: code %d\n", Null_Ptr);
        return Null_Ptr;
    }

    if (stk->data == nullptr)
    {
        ColorPrint(RedColor, "Error StackError: code %d\n", Null_Data_Ptr);
        return Null_Data_Ptr;
    }

    if ((stk->size > stk->capacity) || (stk->size < 0))
    {
        ColorPrint(RedColor, "Error StackError: code %d\n", Error_Size);
        return Error_Size;
    }

    if (stk->capacity < 0)
    {
        ColorPrint(RedColor, "Error StackError: code %d\n", Error_Capacity);
        return Error_Capacity;
    }
    
    return No_Errors;
}

int StackDump(Stack* stk)
{
    if (stk == nullptr)
    {
        ColorPrint(RedColor, "Error StackDump: code %d\n", Null_Ptr);
        return Null_Ptr;
    }

    ColorPrint(RedColor, "Elems:\n"); 

    int err = StackError(stk);

    if (err != Null_Data_Ptr)
    {
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
    }

    ColorPrint(RedColor, "size: %d\ncapacity: %d\nError code: %d\n", stk->size, stk->capacity, err);

    return err;
}

int Recalloc(Stack* stk, int old_size, int new_capacity)
{
    int err = No_Errors;

    if ((err = StackError(stk)))
    {
        ColorPrint(RedColor, "Error Recalloc: code %d\n", err);
        return err;
    }

    stk->data = (stack_type*) realloc(stk->data, new_capacity * sizeof(stack_type));
    
    if((err = StackError(stk)))
    {
        ColorPrint(RedColor, "Error Recalloc: code %d\n", err);
        return err;
    }

    memset(stk->data + old_size, 0, (new_capacity - old_size) * sizeof(stack_type));

    return err;
}

void StackAssert(Stack* stk)
{
    int err = No_Errors;

    if ((err = StackError(stk)))
    {
        StackDump(stk);
        ColorPrint(RedColor, "Error StackAssert: code %d\n", err);

        assert(nullptr);
    }
}

int IncrStackSize(Stack* stk)
{
    int err = No_Errors;

    if ((err = StackError(stk)))
    {
        ColorPrint(RedColor, "Error IncrStackSize: code %d\n", err);
        return err;
    }

    if (stk->size == stk->capacity)
    {
        stk->capacity = (int) stk->capacity * 1.4 + 10;
        err = Recalloc(stk, stk->size, stk->capacity);
    }
    
    if (err)
    {
        //DEBUG(err);
        ColorPrint(RedColor, "Error IncrStackSize: code %d\n", err);
        return err;
    }

    (stk->size)++;

    return err;
}

int DecrStackSize(Stack* stk)
{
    int err = No_Errors;

    if ((err = StackError(stk)))
    {
        ColorPrint(RedColor, "Error Recalloc: code %d\n", err);
        return err;
    }

    (stk->size)--;

    if (stk->size <= stk->capacity / 2.5 - 5)
    {
        if ((err = Recalloc(stk, stk->size, stk->capacity / 2)))
        {
            ColorPrint(RedColor, "Error Recalloc: code %d\n", Null_Ptr);
            return err;
        }

        stk->capacity /= 2;
    }

    return err;
}
