#ifndef SERVICE_STACK_FUNC_H
#define SERVICE_STACK_FUNC_H

#include "stack.h"

int StackError(Stack* stk);

int StackDump(Stack* stk ON_DEBUG(, const char* file, int line));

void StackAssert(Stack* stk);

int Recalloc(Stack* stk, int old_size, int new_size);

void PrintError(int err, const char* file, int line, const char* func);

long long Hash_Data(Stack* stk);

long long Hash_Stack(Stack* stk);

long long Hash_Str(const char* str);

#endif // SERVICE_STACK_FUNC_H