#ifndef ___LINKEDLIST___
#define ___LINKEDLIST___

typedef struct linkedlist_t linkedlist;

linkedlist  *linkedlist_create  (int val);
void        linkedlist_destroy  (linkedlist *list);
void        linkedlist_add_head (linkedlist *list, int val);
void        linkedlist_add_tail (linkedlist *list, int val);
void        linkedlist_pop_head (linkedlist *list);
void        linkedlist_pop_tail (linkedlist *list);
int         linkedlist_size     (linkedlist *list);
void        linkedlist_set      (linkedlist *list, unsigned int pos, int val);
int         linkedlist_get      (linkedlist *list, unsigned int pos);
void        linkedlist_print    (linkedlist *list);
void        linkedlist_insert   (linkedlist *list, unsigned int pos, int val);
void        linkedlist_remove   (linkedlist *list, unsigned int pos);

#endif
