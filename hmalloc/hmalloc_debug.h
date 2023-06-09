#ifndef ___HMALLOC___DEBUG___
#define ___HMALLOC___DEBUG___

#define hmalloc(n) debug_hmalloc(n)
#define hfree(ptr) debug_hfree(ptr)
#define hrealloc(ptr, size) debug_hrealloc(ptr, size)
#define hcalloc(size, n) debug_hcalloc(size, n)
#define hreturn() debug_hreturn()

#endif
