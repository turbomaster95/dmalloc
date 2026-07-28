#include <stdint.h>
#include <stddef.h>
#include "glue.h"
#include "dmalloc.h"

extern uint8_t *bump_ptr;
extern uint8_t *heap_end;
extern Header *free_list;

void *calloc(size_t nmemb, size_t size) {
    size_t total_size = nmemb * size;

    if (nmemb != 0 && total_size / nmemb != size) return NULL;

    void *ptr = malloc(total_size);
    if (ptr) {
        uint8_t *byte_ptr = (uint8_t *)ptr;
        for (size_t i = 0; i < total_size; i++) {
            byte_ptr[i] = 0;
        }
    }
    return ptr;
}
