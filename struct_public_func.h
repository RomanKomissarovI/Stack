#ifndef STRUCT_PUBLIC_FUNC
#define STRUCT_PUBLIC_FUNC

#include "struct.h"
#include "struct_private_func.h"

void StackPush(Stack* stk, stack_type a);

void StackPop(Stack* stk);

void StackCtor(Stack* stk);

void StackDtor(Stack* stk);

#endif // STRUCT_PUBLIC_FUNC