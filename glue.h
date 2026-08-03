#ifndef GLUE_H
#define GLUE_H

#include <stddef.h>

// Allocates clean page(s)
void *pal_mmap(size_t bytes);

// Releases mapped page(s)
int pal_munmap(void *addr, size_t bytes);

#ifdef GIMPL

#include <sys/types.h>
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);

#define MAP_PRIVATE    0x02
#define MAP_ANON       0x20
#define MAP_ANONYMOUS  MAP_ANON
#define MAP_FAILED ((void *) -1)
#define PROT_READ      1
#define PROT_WRITE     2

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
