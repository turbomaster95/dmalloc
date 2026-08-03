#include <stdint.h>
#include <stddef.h>
#include "glue.h"
#include "dmalloc.h"

extern uint8_t *bump_ptr;
extern uint8_t *heap_end;
extern Header *free_list;

void free(void *ptr) {
    if (!ptr) return;

    Header *header = (Header *)ptr - 1;

    if (header->is_mmapped) {
        size_t total_size = sizeof(Header) + header->size;
        pal_munmap(header, total_size);
        return;
    }

    header->next = free_list;
    free_list = header;
}
