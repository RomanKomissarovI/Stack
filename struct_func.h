#ifndef STRUCT_PUBLIC_FUNC
#define STRUCT_PUBLIC_FUNC

#include "struct.h"

int StackPush(Stack* stk, stack_type a);

int StackPop(Stack* stk);

int StackCtor(Stack* stk ON_DEBUG(, const char* name, const char* file, int line));

int StackDtor(Stack* stk);



int StackError(Stack* stk);

int StackDump(Stack* stk ON_DEBUG(, const char* name, const char* file, int line));

void StackAssert(Stack* stk);

int Recalloc(Stack* stk, int old_size, int new_size);

void PrintError(int err, const char* file, int line, const char* func);

#endif // STRUCT_PUBLIC_FUNC