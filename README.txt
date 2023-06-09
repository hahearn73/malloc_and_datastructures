Harry Ahearn
less of a true README, more general regards from program author

read this tutorial beforehand for basic ideas: https://danluu.com/malloc-tutorial/
notable similarities:
    struct block_meta
    use of an implicit list
    use of sbrk instead of mmap

notes for my implementation:
    implemented functions to get rid of external and internal fragmentation
    merge_free_blocks() and separate_blocks(struct block_meta *curr, size_t size)
    merge is called by hfree(void *ptr) and merges adjacent free blocks into
    singular blocks (external fragmentation)
    separate is called by hmalloc and hrealloc and takes a block and splits
    it into two adjacent blocks based on the size parameter, size being the size
    of the first block (internal fragmentation)
    added a debugger using macros
    added the ability to give the whole heap back to the os using hreturn as
    hfree just gives it back to the implicit list to be used again for another
    hmalloc call
    hreturn uses brk!
    added hcalloc
    reallocing non already alloced ptr (ptr? u mean chunk!) is undefined

used my custom malloc - hmalloc - to implement common data structures I had
previously made for fun. just as an exercise in understanding basics of
how malloc works under the hood

I know there is a better way to do the Makefile...

got to make debug functions that are mapped to using #define. User gets to
use original functions with added benefit of printing debug info to screen with
each call. Essentially an incredibly lightweight memory debugger when used
to keep track of hmalloc.h calls.

future ideas based on this project:
    make a thread safe malloc
    make malloc using an explicit list
