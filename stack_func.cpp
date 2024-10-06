#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stack_func.h"

static FILE* output = fopen("output.txt", "w");
static const long long k_Hash_xor = 65535;
static const long long k_Hash_init = 7914;
static const long long k_Hash_mod = 1e9 + 7;

int StackPush(Stack* stk, stack_t a)
{
    int err = No_Errors;

    err = StackError(stk);
    DEBUG_PR_ERR(err);

    if (stk->size == stk->capacity)
    {
        err = Recalloc(stk, stk->size, (int) stk->capacity * 1.4 + 10);
    }

    DEBUG_PR_ERR(err);

    ON_DEBUG(stk->hash_stack = (stk->hash_stack - (stk->size ^ k_Hash_xor)) % k_Hash_mod;)
    (stk->size)++;
    ON_DEBUG(stk->hash_stack = (stk->hash_stack + (stk->size ^ k_Hash_xor)) % k_Hash_mod;)

    *((stack_t*) stk->data + stk->size - 1) = a;
    ON_DEBUG(stk->hash_data = (stk->hash_data + (k_Hash_xor ^ a)) % k_Hash_mod;)

    ON_DEBUG(err = StackError(stk);
    DEBUG_PR_ERR(err);)

    return err;
}

int StackPop(Stack* stk)
{
    int err = No_Errors;

    err = StackError(stk);
    DEBUG_PR_ERR(err);

    if (stk->size - 1 <= stk->capacity / 2.5 - 5)
    {
        err = Recalloc(stk, stk->size, stk->capacity / 2);
        DEBUG_PR_ERR(err);
    }

    ON_DEBUG(stk->hash_stack = (stk->hash_stack - (stk->size ^ k_Hash_xor)) % k_Hash_mod;)
    (stk->size)--;
    ON_DEBUG(stk->hash_stack = (stk->hash_stack + (stk->size ^ k_Hash_xor)) % k_Hash_mod;)

    stack_t* a = (stack_t*) stk->data + stk->size;
    ON_DEBUG(stk->hash_data = (k_Hash_mod + stk->hash_data - (k_Hash_xor ^ (*a))) % k_Hash_mod;)

    *a = (stack_t) 0;

    ON_DEBUG(err = StackError(stk);
    DEBUG_PR_ERR(err);)

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
    ON_DEBUG(stk->hash_data = k_Hash_init;)
    ON_DEBUG(stk->hash_stack = Hash_Stack(stk);)

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
    ON_DEBUG(stk->hash_data = -1;)
    ON_DEBUG(stk->hash_stack = -1;)

    stk->capacity = 0;
    stk->size = 0;
    ON_DEBUG(stk->data -= sizeof(canar_t);)
    Free(stk->data);

    return err;
}