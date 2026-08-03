#include <stdint.h>
#include <stddef.h>
#include "dmalloc.h"

#define GIMPL
#include "glue.h"

uint8_t *bump_ptr;
uint8_t *heap_end;
Header *free_list = NULL;

#define INITIAL_HEAP_SIZE (1024 * 1024) // 1MB Default Heap

void minit(void *memory, size_t mem_size) {
    bump_ptr = (uint8_t *)memory;
    heap_end = bump_ptr + mem_size;
    free_list = NULL;
}

static Header *dalloc(size_t size) {
    if (size == 0) return NULL;
    Header **curr = &free_list;
    while (*curr) {
        if ((*curr)->size >= size) {
            Header *reused = *curr;
            *curr = reused->next;
            return reused;
        }
        curr = &(*curr)->next;
    }

    size_t total_size = sizeof(Header) + size;
    if (bump_ptr + total_size > heap_end) return NULL;

    Header *header = (Header*)bump_ptr;
    header->size = size;
    bump_ptr += total_size;

    return header;
}

void *malloc(size_t size) {
    if (size == 0) return NULL;

    size_t total_size = sizeof(Header) + size;

    if (size >= MMAP_THRESHOLD) {
        Header *header = (Header *)pal_mmap(total_size);
        if (!header) return NULL;

        header->size = size;
        header->next = NULL;
        header->is_mmapped = 1;

        return (void *)(header + 1);
    }

    if (!bump_ptr) {
        void *mem = pal_mmap(INITIAL_HEAP_SIZE);
        if (!mem) return NULL;
        minit(mem, INITIAL_HEAP_SIZE);
    }

    Header *header = dalloc(size); 
    if (!header) return NULL;

    header->is_mmapped = 0;
    return (void *)(header + 1);
}

