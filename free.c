#include <stdint.h>
#include <stddef.h>
#include "glue.h"
#include "dmalloc.h"

extern uint8_t *bump_ptr;
extern uint8_t *heap_end;
extern Header *free_list;

void free(void *ptr) {
    if (!ptr) return;

    // the header sits right before the data pointer
    Header *header = (Header *)ptr - 1;

    // put onto the free list stack
    header->next = free_list;
    free_list    = header;
}
