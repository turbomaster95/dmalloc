#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "glue.h"
#include "dmalloc.h"

extern uint8_t *bump_ptr;
extern uint8_t *heap_end;
extern Header *free_list;

void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    Header *header = (Header *)ptr - 1;
    size_t old_size = header->size;

    void *new_ptr = malloc(size);
    if (new_ptr) {
        size_t copy_size = (size < old_size) ? size : old_size;
        memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }

    return new_ptr;
}
