#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "arraylist.h"
#include "hmalloc.h"

void expand(arraylist *arr);
void shrink(arraylist *arr);

struct arraylist_t {
    int *arr;
    unsigned int size;
    unsigned int capacity;
};

int arraylist_size(arraylist *arr)
{
    return arr->size;
}

arraylist *arraylist_create(int size)
{
    assert(size > 0);
    arraylist *ret = (arraylist *) hmalloc(sizeof(arraylist));
    ret->arr = (int *) hmalloc(sizeof(int) * size);
    ret->size = 0;
    ret->capacity = size;
    return ret;
}

void arraylist_destroy(arraylist *arr)
{
    hfree(arr->arr);
    hfree(arr);
}

void arraylist_append(arraylist *arr, int n)
{
    if (arr->size < arr->capacity - 1) {
        arr->arr[arr->size] = n;
        arr->size = arr->size + 1;
    }
    else {
        expand(arr);
        arr->arr[arr->size] = n;
        arr->size = arr->size + 1;
    }
}

void arraylist_print(arraylist *arr)
{
    printf("size: %d, capacity: %d\t", arr->size, arr->capacity);
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->arr[i]);
    }
    printf("\n");
}

void expand(arraylist *arr)
{
    arr->arr = (int *) hrealloc(arr->arr, sizeof(int) * arr->capacity * 2 + 1);
    arr->capacity = arr->capacity * 2 + 1;
}

int arraylist_remove_at(arraylist *arr, unsigned int pos)
{
    assert(pos < arr->size);
    int ret = arr->arr[pos];
    for (int i = pos; i < arr->size - 1; i++) {
        arr->arr[i] = arr->arr[i + 1];
    }
    if (arr->size < arr->capacity / 2) {
        shrink(arr);
    }
    arr->size = arr->size - 1;
    return ret;
}

inline int arraylist_remove_last(arraylist *arr)
{
    return arraylist_remove_at(arr, arr->size - 1);
}


void shrink(arraylist *arr)
{
    arr->arr = (int *) hrealloc(arr->arr, sizeof(int) * arr->capacity / 2);
    arr->capacity = arr->capacity / 2;
}

void arraylist_set(arraylist *arr, unsigned int pos, int n)
{
    assert(pos < arr->size);
    arr->arr[pos] = n;
}

int arraylist_get(arraylist *arr, unsigned int pos)
{
    assert(pos < arr->size);
    return arr->arr[pos];
}
