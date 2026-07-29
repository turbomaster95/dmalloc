#ifndef GLUE_H
#define GLUE_H

#include <stddef.h>

// Allocates clean page(s)
void *pal_mmap(size_t bytes);

// Releases mapped page(s)
int pal_munmap(void *addr, size_t bytes);

#ifdef GIMPL
void *pal_mmap(size_t bytes) {
    void *ptr = mmap(NULL, bytes, PROT_READ | PROT_WRITE, 
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
                     
    if (ptr == MAP_FAILED) return NULL;
    return ptr;
}

int pal_munmap(void *addr, size_t bytes) {
    return munmap(addr, bytes);
}
#endif

#endif
