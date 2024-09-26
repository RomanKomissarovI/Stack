#include <assert.h>
#include <stdlib.h>
#include "struct_public_func.h"
//#include "struct_private_func.h"    // del '//'
#include "color_print.h"
#include "macroc.h"

int StackPush(Stack* stk, stack_type a)
{
    int err = No_Errors;

    if ((err = IncrStackSize(stk)))
    {
        ColorPrint(RedColor, "Error StackPush: code %d\n", err);
        return err;
    }

    stk->data[stk->size - 1] = a;

    return err;
}

int StackPop(Stack* stk)
{
    int err = No_Errors;

    if ((err = DecrStackSize(stk)))
    {
        ColorPrint(RedColor, "Error StackPop: code %d\n", err);
        return err;
    }

    stk->data[stk->size] = 0;

    return err;
}

int StackCtor(Stack* stk)
{
    int err = No_Errors;

    if (stk == nullptr)
    {
        ColorPrint(RedColor, "Error StackCtor: code %d\n", Null_Ptr);
        return Null_Ptr;
    }

    stk->size = 0;
    stk->capacity = 10;
    stk->data = (stack_type*) calloc(stk->capacity, sizeof(stack_type)); 

    if ((err = StackError(stk)))
    {
        ColorPrint(RedColor, "Error StackCtor: code %d\n", Null_Ptr);
        return Null_Ptr;
    }

    return err;
}

int StackDtor(Stack* stk)
{
    int err = No_Errors;

    if (stk == nullptr)
    {
        ColorPrint(RedColor, "Error StackDtor: code %d\n", Null_Ptr);
        return Null_Ptr;
    }

    stk->capacity = 0;
    stk->size = 0;
    Free(stk->data);

    return err;
}