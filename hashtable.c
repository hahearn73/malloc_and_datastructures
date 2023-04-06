#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "hmalloc.h"

#define TABLE_SIZE 1024
#define EMPTY -1

int hash(int val);
inline int hash(int val)
{
    return val % TABLE_SIZE;
}

void hashtable_print(hashtable *table)
{
    int *arr = (int *) table;
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

hashtable *hashtable_create()
{
    int* table = (int *) hmalloc(sizeof(int) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = EMPTY;
    return (hashtable *) table;
}

void hashtable_destroy(hashtable *table)
{
    hfree(table);
}

void hashtable_insert(hashtable *table, unsigned int val)
{
    int pos = hash(val);
    int *arr = (int *) table;
    if (arr[pos] == EMPTY) {
        arr[pos] = val;
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (arr[(pos + i) % TABLE_SIZE] == EMPTY) {
            arr[(pos + i) % TABLE_SIZE] = val;
            return;
        }
    }
}

int hashtable_contains(hashtable *table, unsigned int val)
{
    int pos = hash(val);
    int *arr = (int *) table;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (arr[(pos + i) % TABLE_SIZE] == val) {
            return 1;
        }
    }
    return 0;
}
