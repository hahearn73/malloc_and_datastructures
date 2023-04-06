#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "arraylist.h"
#include "linkedlist.h"
#include "hashtable.h"
#include "stack.h"
#include "hmalloc.h"
// #include "hmalloc_debug.h"

void test_stack();
void test_malloc();
void test_malloc_fragmentation(); // should run first
void test_arraylist();
void test_linkedlist();
void test_hashtable();

int main()
{
    test_malloc_fragmentation();
    test_arraylist();
    test_linkedlist();
    test_hashtable();
    test_stack();
    test_malloc();

    return 0;
}

void test_arraylist()
{
    arraylist *arr = arraylist_create(5);
    for (int i = 0; i < 10; i++) {
        arraylist_append(arr, i);
    }
    arraylist_print(arr);
    for (int i = 9; i >= 0; i--) {
        arraylist_remove_at(arr, i);
        arraylist_print(arr);
    }
    arraylist_print(arr);
    for (int i = 0; i < 10; i++) {
        arraylist_append(arr, i);
    }
    arraylist_print(arr);
    for (int i = 0; i < 10; i++) {
        arraylist_remove_last(arr);
    }
    arraylist_print(arr);
    for (int i = 0; i < 10; i++) {
        arraylist_append(arr, i);
    }
    arraylist_print(arr);
    for (int i = 0; i < 10; i++) {
        arraylist_set(arr, i, 10 - i);
    }
    arraylist_print(arr);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", arraylist_get(arr, i));
    }
    arraylist_destroy(arr);
}

void test_linkedlist()
{
    linkedlist *list = linkedlist_create(0);
    for (int i = 0; i < 10; i++) {
        linkedlist_add_head(list, i);
        linkedlist_print(list);
    }
    for (int i = 0; i < 10; i++) {
        linkedlist_add_head(list, i);
        linkedlist_print(list);
    }
    for (int i = 0; i < 10; i++) {
        linkedlist_pop_head(list);
        linkedlist_print(list);
    }
    for (int i = 0; i < 11; i++) {
        linkedlist_pop_tail(list);
        linkedlist_print(list);
    }

    for (int i = 0; i < 10; i++) {
        linkedlist_insert(list, i, i);
        linkedlist_print(list);
    }
    linkedlist_print(list);
    for (int i = 9; i >= 0; i--) {
        linkedlist_remove(list, i);
        linkedlist_print(list);
    }
    linkedlist_print(list);
    linkedlist_destroy(list);
}

void test_hashtable()
{
    hashtable *table = hashtable_create();
    srand(time(NULL));
    for (int i = 0; i < 50; i++) {
        hashtable_insert(table, rand() % 501);
    }
    // hashtable_print(table);
    for (int i = 0; i < 100; i++) {
        hashtable_insert(table, rand() % 501);
    }
    // hashtable_print(table);
    hashtable_destroy(table);

    table = hashtable_create();
    for (int i = 0; i < 50; i++) {
        hashtable_insert(table, i);
    }
    for (int i = 0; i < 100; i++) {
        int bool = hashtable_contains(table, i);
        if (bool)
            printf("1 ");
        else
            printf("0 ");
    }
    printf("\n");
    hashtable_destroy(table);
}

void test_stack()
{
    stack *st = stack_create();
    for (int i = 0; i < 10; i++) {
        stack_push(st, i);
    }
    stack_print(st);
    for (int i = 0; i < 10; i++) {
        printf("%d ", stack_pop(st));
    }
    stack_print(st);
    stack_destroy(st);
}

struct block_meta {
    struct block_meta *next;
    int size;
    int free;
};
#define META_SIZE sizeof(struct block_meta)

void test_malloc()
{
    int *arr = (int *) hmalloc(sizeof(int) * 50);
    for (int i = 0; i < 50; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < 50; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int *arr2 = (int *) hmalloc(sizeof(int) * 100);
    hfree(arr2);
    char *c = (char *) hmalloc(sizeof(char) * 20);
    hfree(c);

    void *temp = arr;
    arr = (int *) hrealloc(arr, sizeof(int) * 10);
    assert(arr == temp);

    arr = (int *) hrealloc(arr, sizeof(int) * 75);
    for (int i = 0; i < 50; i ++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    assert(arr != temp);
    hfree(arr);
}

void test_malloc_fragmentation()
{
    printf("TEST: fragmentation\n");
    char *a1 = (char *) hmalloc(sizeof(char) * 100);
    char *a2 = (char *) hmalloc(sizeof(char) * 500);
    char *a3 = (char *) hmalloc(sizeof(char) * 500);
    char *a4 = (char *) hmalloc(sizeof(char) * 100);

    hfree(a2);
    hfree(a3);

    char *a5 = (char *) hmalloc(sizeof(char) * 700);

    // put back in .h file to use
    // print_next(a1);
    printf("%p %p %p\n", a1, a4, a5);
    // is_next(a1, a5); // proves merge free block
    // next line proves separate blocks
    // is_next(a5, a4); // should fail, a5 points at empty block, not a4
    hfree(a1);
    hfree(a5);
    hfree(a4);
}
