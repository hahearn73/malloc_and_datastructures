#ifndef ___HMALLOC___
#define ___HMALLOC___

void    *hmalloc    (size_t size);
void    hfree       (void *ptr);
void    *hrealloc   (void *ptr, size_t size);
void    *hcalloc    (size_t size, int n);
void    hreturn     ();

// mem debug funcs, put #include "hmalloc_debug.h" in file to be debugged
// these functions replace their non-debug versions using macros in .h file
void    *debug_hmalloc  (size_t size);
void    debug_hfree     (void *ptr);
void    *debug_hrealloc (void *ptr, size_t size);
void    *debug_hcalloc  (size_t size, int n);
void    debug_hreturn   ();

#endif
