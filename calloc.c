#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "glue.h"
#include "dmalloc.h"

void *calloc(size_t nmemb, size_t size) {
    size_t total_size;
    
    if (__builtin_mul_overflow(nmemb, size, &total_size)) {
        return NULL;
    }

    void *ptr = malloc(total_size);
    if (ptr) {
        memset(ptr, 0, total_size);
    }
    return ptr;
}
