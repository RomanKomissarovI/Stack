#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stack_func.h"

ON_DEBUG(static FILE* output = fopen("output.txt", "w");)

int StackPush(Stack* stk, stack_t a)
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

    *((stack_t*) stk->data + stk->size - 1) = a;

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

    *((stack_t*) stk->data + stk->size) = (stack_t) 0;

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

    stk->data = (char*) calloc(ON_DEBUG(2 * sizeof(canar_t) + 7 + ) stk->capacity * sizeof(stack_t), sizeof(char)); 

    ON_DEBUG(*(canar_t*) stk->data = k_Canar;)
    ON_DEBUG(stk->data += sizeof(canar_t);)
    ON_DEBUG(size_t ptr_right_canar = (size_t) stk->data + stk->capacity * sizeof(stack_t);)
    ON_DEBUG(*(canar_t*) (ptr_right_canar + (sizeof(canar_t) - ptr_right_canar % sizeof(canar_t)) % sizeof(canar_t)) = k_Canar;)

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
    ON_DEBUG(stk->data -= sizeof(canar_t);)
    Free(stk->data);

    return err;
}











int StackError(Stack* stk)
{
    int err = No_Errors;
    if(stk == nullptr)
    {
        err = Null_Ptr;
        DEBUG_PR_ERR(err);
    }

    if (stk->data == nullptr)
    {
        err = Null_Data_Ptr;
        DEBUG_PR_ERR(err);
    }

    ON_DEBUG(size_t ptr_right_canar = (size_t) stk->data + stk->capacity * sizeof(stack_t);)
    ON_DEBUG(canar_t c = *(canar_t*) (ptr_right_canar + (sizeof(canar_t) - ptr_right_canar % sizeof(canar_t)) % sizeof(canar_t));)

    if ((*(canar_t*) (stk->data - 8) != k_Canar) || (c != k_Canar))
    {
        err = Error_Canar;
        DEBUG_PR_ERR(err);
    }

    if ((stk->size > stk->capacity) || (stk->size < 0))
    {
        err = Error_Size;
        DEBUG_PR_ERR(err);
    }

    if (stk->capacity < 0)
    {
        err = Error_Capacity;
        DEBUG_PR_ERR(err);
    }
    
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
        char* elem_now = stk->data;
        while (i < size)
        {
            ColorPrint(RedColor, "%d ", *(stack_t*) elem_now);

            ++i;
            elem_now += sizeof(stack_t);

            if (i % 20 == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
    }

    ColorPrint(RedColor, "size: %d\ncapacity: %d\nError code: %d\n", stk->size, stk->capacity, err);
    ColorPrint(RedColor, "Error found: file: %s, line: %d, name_val: %s\n", file, line, name);

    return err;
}

int Recalloc(Stack* stk, int old_size, int new_capacity)
{
    int err = No_Errors;

    if (stk == nullptr)
    {
        DEBUG_PR_ERR(Null_Ptr);
    }
    //printf("RIGHT CANAR: %d\n", (size_t) (stk->data + old_size * sizeof(stack_t)) % 8);

    ON_DEBUG(stk->data -= sizeof(canar_t);)
    stk->data = (char*) realloc(stk->data, ON_DEBUG(2 * sizeof(canar_t) + 7 + ) new_capacity * sizeof(stack_t));
    
    if (stk->data == nullptr)
    {
        DEBUG_PR_ERR(Null_Data_Ptr);
    }
    //DEBUG_PR_ERR(err);

    ON_DEBUG(stk->data += sizeof(canar_t);)
    memset(stk->data + old_size * sizeof(stack_t), 0, (new_capacity - old_size) * sizeof(stack_t));
    ON_DEBUG(size_t ptr_right_canar = (size_t) stk->data + new_capacity * sizeof(stack_t);)
    ON_DEBUG(*(canar_t*) (ptr_right_canar + (sizeof(canar_t) - ptr_right_canar % sizeof(canar_t)) % sizeof(canar_t)) = k_Canar;)    //ON_DEBUG(printf("RIGHT CANAR: %lld", (size_t) &right_canar);)
    DEBUG_PR_ERR(err);

    // ON_DEBUG(size_t ptr_right_canar = (size_t) stk->data + stk->capacity * sizeof(stack_t);)
    // ON_DEBUG(*(canar_t*) (ptr_right_canar + (sizeof(canar_t) - ptr_right_canar % sizeof(canar_t)) % sizeof(canar_t)) = k_Canar;)

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
