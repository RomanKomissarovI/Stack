#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "struct_func.h"

ON_DEBUG(static FILE* output = fopen("output.txt", "w");)

int StackPush(Stack* stk, stack_type a)
{
    int err = No_Errors;

    err = StackError(stk);
    DEBUG_PR_ERR(err);

    if (stk->size == stk->capacity)
    {
        stk->capacity = (int) stk->capacity * 1.4 + 10;
        err = Recalloc(stk, stk->size, stk->capacity);
    }

    DEBUG_PR_ERR(err);

    (stk->size)++;

    stk->data[stk->size - 1] = a;

    return err;
}

int StackPop(Stack* stk)
{
    int err = No_Errors;

    err = StackError(stk);
    DEBUG_PR_ERR(err);

    (stk->size)--;

    if (stk->size <= stk->capacity / 2.5 - 5)
    {
        err = Recalloc(stk, stk->size, stk->capacity / 2);
        DEBUG_PR_ERR(err);

        stk->capacity /= 2;
    }

    stk->data[stk->size] = 0;

    return err;
}

int StackCtor(Stack* stk ON_DEBUG(, const char* name, const char* file, int line))
{
    int err = stk == nullptr;

    DEBUG_PR_ERR(err);

    stk->size = 0;
    stk->capacity = 10;
    ON_DEBUG(stk->name = name;)
    ON_DEBUG(stk->file = file;)
    ON_DEBUG(stk->line = line;)
    stk->data = (stack_type*) calloc(stk->capacity, sizeof(stack_type)); 

    err = StackError(stk);
    DEBUG_PR_ERR(err);

    return err;
}

int StackDtor(Stack* stk)
{
    int err = stk == nullptr;
    DEBUG_PR_ERR(err);

    ON_DEBUG(stk->name = "";)
    ON_DEBUG(stk->file = "";)
    ON_DEBUG(stk->line = -1;)

    stk->capacity = 0;
    stk->size = 0;
    Free(stk->data);

    return err;
}











int StackError(Stack* stk)
{
    int err = stk == nullptr;
    DEBUG_PR_ERR(err);

    err = stk->data == nullptr;
    DEBUG_PR_ERR(err);

    err = (stk->size > stk->capacity) || (stk->size < 0);
    DEBUG_PR_ERR(err);

    err = stk->capacity < 0;
    DEBUG_PR_ERR(err);
    
    return No_Errors;
}

int StackDump(Stack* stk ON_DEBUG(, const char* name, const char* file, int line))
{
    int err = stk == nullptr;
    DEBUG_PR_ERR(err);

    ColorPrint(RedColor, "Elems:\n"); 
    err = StackError(stk);

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
    int err = StackError(stk);
    DEBUG_PR_ERR(err);

    stk->data = (stack_type*) realloc(stk->data, new_capacity * sizeof(stack_type));
    
    err = StackError(stk);
    DEBUG_PR_ERR(err);

    memset(stk->data + old_size, 0, (new_capacity - old_size) * sizeof(stack_type));

    return err;
}

void StackAssert(Stack* stk)
{
    int err = No_Errors;

    if ((err = StackError(stk)))
    {
        STACK_DUMP(stk);
        PrintError(err, __FILE__, __LINE__, __PRETTY_FUNCTION__);

        assert(nullptr);
    }
}

void PrintError(int err, const char* file, int line, const char* func)
{
    fprintf(output, "file: %s, line: %d, func: %s Error code %d\n", file, line, func, err);
}