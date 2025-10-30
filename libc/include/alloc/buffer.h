#ifndef ALLOC_BUFFER_H
#define ALLOC_BUFFER_H

#include <stdint.h>
#include <alloc.h>

struct buffer_alloc {
    u8 *buffer;
    void *last;
    usize size, pos, last_size;
};

struct alloc buffer_alloc_init(struct buffer_alloc *buf, u8 *buffer,
    usize size);

#endif
