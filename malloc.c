#include <stdint.h>
#include <stddef.h>
#include "glue.h"
#include "dmalloc.h"

uint8_t *bump_ptr;
uint8_t *heap_end;
Header *free_list = NULL;

void minit(void *memory, size_t mem_size) {
    bump_ptr = (uint8_t *)memory;
    heap_end = bump_ptr + mem_size;
    free_list = NULL;
}

void *malloc(size_t size) {
    if (size == 0) return NULL;
    Header **curr = &free_list;
    while (*curr) {
        if ((*curr)->size >= size) {
            Header *reused = *curr;
            *curr = reused->next;
            return (void *)(reused + 1);
        }
        curr = &(*curr)->next;
    }

    // no free block fit??
    size_t total_size = sizeof(Header) + size;
    if (bump_ptr + total_size > heap_end) return NULL; // NOOO!!! OOM!!

    Header *header = (Header*)bump_ptr;
    header->size = size;
    bump_ptr += total_size;

    return (void *)(header + 1);
}
