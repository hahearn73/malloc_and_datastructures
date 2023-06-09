#ifndef ___STACK___
#define ___STACK___

typedef struct stack stack;

stack *stack_create();
void stack_destroy(stack *st);
int stack_pop(stack *st);
void stack_push(stack *st, unsigned int val);
void stack_print(stack *st);

#endif
