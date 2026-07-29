#ifndef DMALLOC_H
#define DMALLOC_H

#include <stddef.h>
#include <stdint.h>

#define MMAP_THRESHOLD (128 * 1024)

typedef struct Header {
  size_t size;
  struct Header *next;
  uint8_t is_mmapped;
} Header;

void *malloc(size_t size);
void free(void *ptr);

#endif
