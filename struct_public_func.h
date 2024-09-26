#ifndef STRUCT_PUBLIC_FUNC
#define STRUCT_PUBLIC_FUNC

#include "struct.h"
#include "struct_private_func.h"  // del

int StackPush(Stack* stk, stack_type a);

int StackPop(Stack* stk);

int StackCtor(Stack* stk);

int StackDtor(Stack* stk);

#endif // STRUCT_PUBLIC_FUNC