#include <string.h>
#include <assert.h>
#include "service_stack_func.h"

static FILE* output = fopen("output.txt", "w");
static const long long k_Hash_xor = 65535;
static const long long k_Hash_init = 7914;
static const long long k_Hash_mod = 1e9 + 7;

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

    ON_DEBUG(if (stk->hash_data != Hash_Data(stk))
    {
        err = Error_Hash_Data;
        DEBUG_PR_ERR(err);
    })

    ON_DEBUG(if (stk->hash_stack != Hash_Stack(stk))
    {
        err = Error_Hash_Stack;
        DEBUG_PR_ERR(err);
    })

    ON_DEBUG(size_t ptr_right_canar = (size_t) stk->data + stk->capacity * sizeof(stack_t);)
    ON_DEBUG(canar_t c = *(canar_t*) (ptr_right_canar + (sizeof(canar_t) - ptr_right_canar % sizeof(canar_t)) % sizeof(canar_t));)

    ON_DEBUG(if ((*(canar_t*) (stk->data - 8) != k_Canar) || (c != k_Canar))
    {
        err = Error_Canar;
        DEBUG_PR_ERR(err);
    })

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

int StackDump(Stack* stk ON_DEBUG(, const char* file, int line))
{
    int err = stk == nullptr;
    DEBUG_PR_ERR(err);

    fprintf(output, "Elems:\n"); 
    err = StackError(stk);

    if (err != Null_Data_Ptr)
    {
        int i = 0;
        int size = (stk->size < stk->capacity) ? stk->size : stk->capacity;
        char* elem_now = stk->data;
        while (i < size)
        {
            fprintf(output, "%d ", *(stack_t*) elem_now);

            ++i;
            elem_now += sizeof(stack_t);

            if (i % 20 == 0)
            {
                fprintf(output, "\n");
            }
        }
        fprintf(output, "\n");
    }

    fprintf(output, "size: %d\ncapacity: %d\nError code: %d\n", stk->size, stk->capacity, err);
    ON_DEBUG(fprintf(output, "Error found: file: %s, line: %d\n", file, line);)
    ON_DEBUG(fprintf(output, "Value created: file: %s, line: %d, name_val: %s\n\n\n\n\n", stk->file, stk->line, stk->name);)

    return err;
}

int Recalloc(Stack* stk, int old_size, int new_capacity)
{
    int err = No_Errors;

    if (stk == nullptr)
    {
        DEBUG_PR_ERR(Null_Ptr);
    }

    ON_DEBUG(stk->hash_stack = (stk->hash_stack - (stk->capacity ^ k_Hash_xor)) % k_Hash_mod;)
    ON_DEBUG(stk->hash_stack = (stk->hash_stack + (new_capacity ^ k_Hash_xor)) % k_Hash_mod;)

    ON_DEBUG(stk->data -= sizeof(canar_t);)
    stk->data = (char*) realloc(stk->data, ON_DEBUG(2 * sizeof(canar_t) + 7 + ) new_capacity * sizeof(stack_t));
    stk->capacity = new_capacity;

    ON_DEBUG(stk->data += sizeof(canar_t);)

    if (stk->data == nullptr)
    {
        DEBUG_PR_ERR(Null_Data_Ptr);
    }

    memset(stk->data + old_size * sizeof(stack_t), '\0', (new_capacity - old_size) * sizeof(stack_t));

    ON_DEBUG(size_t ptr_right_canar = (size_t) stk->data + new_capacity * sizeof(stack_t);)
    ON_DEBUG(*(canar_t*) (ptr_right_canar + (sizeof(canar_t) - ptr_right_canar % sizeof(canar_t)) % sizeof(canar_t)) = k_Canar;)    //ON_DEBUG(printf("RIGHT CANAR: %lld", (size_t) &right_canar);)

    err = StackError(stk);
    DEBUG_PR_ERR(err);

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

long long Hash_Data(Stack* stk)
{
    long long hash = k_Hash_init;
    for (int i = 0; i < stk->size; ++i)
    {
        hash = (hash + ((*(stack_t*) (stk->data + i * sizeof(stack_t))) ^ k_Hash_xor)) % k_Hash_mod;
    }
    return hash;
}

long long Hash_Stack(Stack* stk)
{
    long long hash = k_Hash_init;

    ON_DEBUG(hash = (hash + (Hash_Str(stk->name) ^ k_Hash_xor)) % k_Hash_mod;)
    ON_DEBUG(hash = (hash + (Hash_Str(stk->file) ^ k_Hash_xor)) % k_Hash_mod;)
    ON_DEBUG(hash = (hash + (stk->line ^ k_Hash_xor)) % k_Hash_mod;)
    hash = (hash + (stk->size ^ k_Hash_xor)) % k_Hash_mod;
    hash = (hash + (stk->capacity ^ k_Hash_xor)) % k_Hash_mod;

    return hash;
}

long long Hash_Str(const char* str)
{
    long long hash = k_Hash_init;
    while (*str != '\0')
    {
        hash = (hash + ((*str++) ^ k_Hash_xor)) % k_Hash_mod;
    }
    return hash;
}