#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "linkedlist.h"
#include "hmalloc.h"

struct node;

typedef struct node {
    int val;
    struct node *next;
    struct node *prev;
} node;

struct linkedlist_t {
    node *head;
    node *tail;
    unsigned int size;
};

linkedlist *linkedlist_create(int val)
{
    linkedlist *ret = (linkedlist *) hmalloc(sizeof(linkedlist));
    node *new_node = (node *) hmalloc(sizeof(node));
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->val = val;
    ret->size = 1;
    ret->head = new_node;
    ret->tail = new_node;
    return ret;
}

void linkedlist_destroy(linkedlist *list)
{
    node *cur = list->head;
    node *temp;
    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        hfree(temp);
    }
    hfree(list);
}

void linkedlist_add_head(linkedlist *list, int val)
{
    node *temp = (node *) hmalloc(sizeof(node));
    temp->val = val;
    if (list->size == 0) {
        temp->next = NULL;
        temp->prev = NULL;
        list->head = temp;
        list->tail = temp;
        list->size = list->size + 1;
        return;
    }
    temp->next = list->head;
    temp->prev = NULL;
    list->head->prev = temp;
    list->head = temp;
    list->size = list->size + 1;
}

void linkedlist_add_tail(linkedlist *list, int val)
{
    node *temp = (node *) hmalloc(sizeof(node));
    temp->val = val;
    if (list->size == 0) {
        temp->next = NULL;
        temp->prev = NULL;
        list->head = temp;
        list->tail = temp;
        list->size = list->size + 1;
        return;
    }
    temp->prev = list->tail;
    temp->next = NULL;
    list->tail->next = temp;
    list->tail = temp;
    list->size = list->size + 1;
}

void linkedlist_print(linkedlist *list)
{
    printf("size: %d\n", list->size);
    node *cur = list->head;
    while (cur != NULL) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

inline int linkedlist_size(linkedlist *list)
{
    return list->size;
}

void linkedlist_pop_head(linkedlist *list)
{
    assert(list->size > 0);
    if (list->size == 1) {
        hfree(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }
    node *temp = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    list->size = list->size - 1;
    hfree(temp);
}

void linkedlist_pop_tail(linkedlist *list)
{
    assert(list->size > 0);
    if (list->size == 1) {
        hfree(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
        return;
    }
    node *temp = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    list->size = list->size - 1;
    hfree(temp);
}

void linkedlist_set(linkedlist *list, unsigned int pos, int val)
{
    assert(pos < list->size);
    int c = 0;
    node *cur = list->head;
    while (cur != NULL) {
        if (c == pos) {
            cur->val = val;
            return;
        }
        c++;
    }
}

int linkedlist_get(linkedlist *list, unsigned int pos)
{
    assert(pos < list->size);
    int c = 0;
    node *cur = list->head;
    while (cur != NULL) {
        if (c == pos) {
            return cur->val;
        }
        c++;
    }
    return -1;
}

void linkedlist_insert(linkedlist *list, unsigned int pos, int val)
{
    assert(pos <= list->size);
    if (pos == 0) {
        linkedlist_add_head(list, val);
        return;
    }
    if (pos == list->size) {
        linkedlist_add_tail(list, val);
        return;
    }
    int c = 0;
    node *cur = list->head;
    while (cur != NULL) {
        if (c == pos - 1) {
            node *temp = (node *) hmalloc(sizeof(node));
            temp->prev = cur;
            temp->next = cur->next;
            cur->next = temp;
            cur->next->prev = temp;
            temp->val = val;
            list->size = list->size + 1;
            return;
        }
        c++;
    }
}

void linkedlist_remove(linkedlist *list, unsigned int pos)
{
    assert(pos < list->size);
    if (pos == 0) {
        linkedlist_pop_head(list);
        return;
    }
    if (pos == list->size - 1) {
        linkedlist_pop_tail(list);
        return;
    }
    int c = 0;
    node *cur = list->head;
    while (cur != NULL) {
        if (c == pos - 1) {
            node *temp = cur->next;
            cur->next = temp->next;
            temp->next->prev = cur;
            hfree(temp);
            list->size = list->size - 1;
            return;
        }
        c++;
    }
}
