#ifndef ___ARRAYLIST___
#define ___ARRAYLIST___

typedef struct arraylist_t arraylist;

void        arraylist_append        (arraylist *arr, int n);
int         arraylist_remove_at     (arraylist *arr, unsigned int pos);
int         arraylist_remove_last   (arraylist *arr);
void        arraylist_set           (arraylist *arr, unsigned int pos, int n);
int         arraylist_get           (arraylist *arr, unsigned int pos);
arraylist   *arraylist_create       (int size);
void        arraylist_destroy       (arraylist *arr);
void        arraylist_print         (arraylist *arr);
int         arraylist_size          (arraylist *arr);

#endif
