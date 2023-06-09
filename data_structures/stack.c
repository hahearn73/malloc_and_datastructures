#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "arraylist.h"
#include "hmalloc.c"

typedef struct stack {
    arraylist *arr;
    int sp;
} stack;

stack *stack_create()
{
    stack *st = (stack *) hmalloc(sizeof(stack));
    st->arr = arraylist_create(50);
    st->sp = -1;
    return st;
}

void stack_destroy(stack *st)
{
    arraylist_destroy(st->arr);
    hfree(st);
}

int stack_pop(stack *st)
{
    if (st->sp < 0)
        return -1;
    st->sp = st->sp - 1;
    return arraylist_remove_last(st->arr);
}

void stack_push(stack *st, unsigned int val)
{
    st->sp = st->sp + 1;
    arraylist_append(st->arr, val);
}

void stack_print(stack *st)
{
    for (int i = st->sp; i >= 0; i--)
        printf("%d ", arraylist_get(st->arr, i));
    printf("\n");
}
