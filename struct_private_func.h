#ifndef STRUCT_PRIVATE_FUNC
#define STRUCT_PRIVATE_FUNC

#include <stdio.h>
#include "struct.h"

int StackError(Stack* stk);

void StackNull(Stack* stk);

void StackDump(Stack* stk);

void StackAssert(Stack* stk);

void Recalloc(Stack* stk, int old_size, int new_size);

void IncrStackSize(Stack* stk);

void DecrStackSize(Stack* stk);

#endif // STRUCT_PRIVATE_FUNC