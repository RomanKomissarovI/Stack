#ifndef STACK_FUNC_H
#define STACK_FUNC_H

#include "service_stack_func.h"

int StackPush(Stack* stk, stack_t a);

int StackPop(Stack* stk);

int StackCtor(Stack* stk ON_DEBUG(, const char* name, const char* file, int line));

int StackDtor(Stack* stk);

#endif // STACK_FUNC_H