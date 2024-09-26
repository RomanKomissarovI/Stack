#ifndef STRUCT_PRIVATE_FUNC
#define STRUCT_PRIVATE_FUNC

#include <stdio.h>
#include "struct.h"

int StackError(Stack* stk);

int StackDump(Stack* stk);

void StackAssert(Stack* stk);

int Recalloc(Stack* stk, int old_size, int new_size);

int IncrStackSize(Stack* stk);

int DecrStackSize(Stack* stk);

#endif // STRUCT_PRIVATE_FUNC