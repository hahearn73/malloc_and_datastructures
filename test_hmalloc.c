#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hmalloc.h"
#include "hmalloc_debug.h"

// these three funcs should run after each other with no reset
void simple_found();
void simple_append();
void multi_found();

// funcs that reset hmalloc
void no_merge();
void fragmentation_funcs();
void realloc_found();
void realloc_append();

// independent tests
void hfree_nullptr();
void realloc_null();
void realloc_downsize();

int main()
{
    simple_found();
    simple_append();
    multi_found();
    no_merge();
    hfree_nullptr();
    fragmentation_funcs();
    realloc_null();
    realloc_downsize();
    realloc_found();
    realloc_append();
}

// finds open block
void simple_found()
{
    printf("---SIMPLE FOUND---\n");
    void *ptr = hmalloc(100);
    void *temp = ptr;
    hfree(ptr);
    ptr = hmalloc(10);
    assert(temp == ptr);
    hfree(ptr);
}

void simple_append()
{
    printf("---SIMPLE APPEND---\n");
    void *ptr = hmalloc(200);
    hfree(ptr);
}

void multi_found()
{
    printf("---MULTI FOUND---\n");
    void *ptr = hmalloc(500);
    hfree(ptr);
    void *ptrs[30];
    for (int i = 0; i < 30; i++) {
        ptrs[i] = hmalloc(1);
    }
    for (int i = 0; i < 30; i++) {
        hfree(ptrs[i]);
    }
    ptr = hmalloc(400);
    hfree(ptr);
}

void no_merge()
{
    printf("---NO MERGE---\n");
    hmalloc_reset();
    void *ptr = hmalloc(10000);
    void *ptr2 = hmalloc(10);
    void *ptr3 = hmalloc(300);
    hfree(ptr2);
}

void hfree_nullptr()
{
    printf("---HFREE NULLPTR---\n");
    hfree(NULL);
}

void fragmentation_funcs()
{
    printf("---FRAGMENTATION FUNCS---\n");
    hmalloc_reset();
    // section proves that separate_blocks is occuring
    void *ptr = hmalloc(500);
    void *ptr_last = hmalloc(500);
    hfree(ptr);
    ptr = hmalloc(100);
    void *ptr2 = hmalloc(200);
    hfree(ptr);
    hfree(ptr2);
    hfree(ptr_last);
    // order of ptrs in mem should be ptr then ptr2 then ptr_last
    // this shows that the 500 bytes allocated originally to ptr have been
    // separated to accomadate ptr and ptr2
    ptr = hmalloc(400); // should be found and not appended
    // shows that ptr and ptr2s blocks get merged
    hfree(ptr);
}

void realloc_null()
{
    printf("---REALLOC NULL---\n");
    void *ptr = hrealloc(NULL, 50);
    // printf("%ls ", (int *)ptr + 1); // should crash
}

void realloc_downsize()
{
    printf("---REALLOC DOWNSIZE---\n");
    int *ptr = (int *) hmalloc(sizeof(int) * 100);
    void *temp = ptr;
    for (int i = 0; i < 100; i++)
        ptr[i] = i;
    ptr = hrealloc(ptr, 50); // nothing should happen
    assert(temp == ptr);
    for (int i = 0; i < 50; i++)
        printf("%d ", ptr[i]);
    printf("\n");
    hfree(ptr);
}

void realloc_found()
{
    printf("---REALLOC FOUND---\n");
    hmalloc_reset();
    void *temp = hmalloc(500);
    int *ptr = (int *) hmalloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++)
        ptr[i] = i;
    hfree(temp);
    ptr = hrealloc(ptr, sizeof(int) * 110);
    assert(ptr == temp);
    for (int i = 0; i < 100; i++)
        assert(ptr[i] == i);
    for (int i = 100; i < 110; i++)
        ptr[i] = i;
    for (int i = 0; i < 110; i++)
        printf("%d ", ptr[i]);
    printf("\n");
    hfree(ptr);
}

void realloc_append()
{
    printf("---REALLOC APPEND---\n");
    hmalloc_reset();
    int *ptr = (int *) hmalloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++)
        ptr[i] = i;
    ptr = hrealloc(ptr, sizeof(int) * 200);
    hfree(ptr);
}
