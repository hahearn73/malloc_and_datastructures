#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "hmalloc.h"

struct block_meta {
    struct block_meta *next;
    unsigned int size;
    int free;
};
#define META_SIZE sizeof(struct block_meta)

void *base = NULL;

// merges adjacent free blocks in the implicit list
void merge_free_blocks()
{
    if (!base) {
        return;
    }
    struct block_meta *curr = base;
    struct block_meta *last = base;
    while (curr) {
        last = curr;
        curr = curr->next;
        if(!curr) {
            break;
        }
        if (curr->free == 1 && last->free == 1) {
            // printff("merging\n");
            last->next = curr->next;
            last->size = curr->size + last->size + META_SIZE;
            curr = curr->next;
        }
    }
}

// separates memory of curr: new->next = curr->next, curr->next = new
// gives size bytes to curr and curr->size - MS - size to new
void separate_blocks(struct block_meta *curr, size_t size)
{
    assert(curr->free);
    // printff("separating\n");
    struct block_meta *new = (struct block_meta*)(((void*)(curr + 1)) + size);
    new->next = curr->next;
    new->size = curr->size - META_SIZE - size;
    new->free = 1;
    curr->size = size;
    curr->next = new;
    curr->free = 0;
}

void *hmalloc(size_t size)
{
    if (!base) { // first alloc
        struct block_meta *block = sbrk(0);
        void *chunk = sbrk(META_SIZE + size);
        assert(block != (void *)-1 && chunk != (void*)-1);
        assert(block == chunk);
        block->next = NULL;
        block->size = size;
        block->free = 0;
        base = block;
        // printff("first\n");
        return (block + 1);
    }

    // look for free blocks
    struct block_meta *curr = base;
    struct block_meta *last = base;
    while (curr) {
        if (curr->free == 1 && curr->size >= size) { // found block
            // printff("found\n");
            if (curr->size - size > META_SIZE) { // make separate empty block
                separate_blocks(curr, size);
            }
            else {
                curr->free = 0;
            }
            return (curr + 1);
        }
        last = curr;
        curr = curr->next;
    }

    // append if no free blocks found
    struct block_meta *block = sbrk(0);
    void *chunk = sbrk(META_SIZE + size);
    assert(block != (void *)-1 && chunk != (void*)-1);
    assert(block == chunk);
    block->next = NULL;
    block->free = 0;
    block->size = size;
    last->next = block;
    // printff("append\n");
    return (block + 1);
}

// sets block->free to 0, merges adjacent free blocks
void hfree(void *ptr)
{
    if(!ptr) {
        // printff("nothing freed\n");
        return;
    }
    struct block_meta *block = (struct block_meta *)ptr - 1;
    assert(block->free == 0);
    block->free = 1;
    // printff("freed\n");
    merge_free_blocks();
}

void *hrealloc(void *ptr, size_t size)
{
    // simple cases
    if (!ptr) {
        return hmalloc(size);
    }
    struct block_meta *block_ptr = (struct block_meta *)ptr - 1;
    if (block_ptr->size >= size) {
        return ptr;
    }

    // look for free blocks
    struct block_meta *curr = base;
    struct block_meta *last = base;
    while(curr) {
        if (curr->free == 1 && curr->size >= size) { // found block
            // printff("found\n");
            memcpy(curr + 1, ptr, block_ptr->size);
            hfree(ptr);
            if (curr->size - size > META_SIZE) { // make separate empty block
                separate_blocks(curr, size);
            }
            else {
                curr->free = 0;
            }
            return (curr + 1);
        }
        last = curr;
        curr = curr->next;
    }

    // append if no free blocks found
    struct block_meta *block = sbrk(0);
    void *chunk = sbrk(META_SIZE + size);
    assert(block != (void *)-1 && chunk != (void*)-1);
    assert(block == chunk);
    block->next = NULL;
    block->free = 0;
    last->next = block;
    block->size = size;
    memcpy(block + 1, ptr, block_ptr->size);
    // printff("append\n");
    return (block + 1);

}

inline void *hcalloc(size_t size, int n)
{
    return hmalloc(sizeof(size) * n);
}

void hreturn()
{
    brk(base);
    base = NULL;
}

//-----------
// DEBUG FUNCS
inline void *debug_hmalloc(size_t size)
{
    printf("Mallocing %ld bytes\n", size);
    return hmalloc(size);
}

inline void debug_hfree(void *ptr)
{
    printf("Freeing %p\n", ptr);
    hfree(ptr);
}

inline void *debug_hrealloc(void *ptr, size_t size)
{
    printf("Reallocing %p %ld bytes\n", ptr, size);
    return hrealloc(ptr, size);
}

inline void *debug_hcalloc(size_t size, int n)
{
    printf("Callocing %ld * %d bytes\n", size, n);
    return hcalloc(size, n);
}

inline void debug_hreturn()
{
    printf("hreturn called, base reset\n");
    hreturn();
}
