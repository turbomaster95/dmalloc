#ifndef DMALLOC_H
#define DMALLOC_H

#include <stddef.h>
#include <stdint.h>

typedef struct Header {
  size_t size;
  struct Header *next;
} Header;

void *malloc(size_t size);
void free(void *ptr);

#endif
