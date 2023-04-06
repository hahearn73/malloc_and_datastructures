#ifndef ___HASHTABLE___
#define ___HASHTABLE___

typedef void* hashtable;

hashtable   *hashtable_create   ();
void        hashtable_destroy   (hashtable *table);
void        hashtable_insert    (hashtable *table, unsigned int val);
int         hashtable_contains  (hashtable *table, unsigned int val);
void        hashtable_print     (hashtable *table);

#endif
