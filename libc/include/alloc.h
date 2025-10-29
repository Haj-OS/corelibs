#ifndef ALLOC_H
#define ALLOC_H

#include <stdint.h>

struct alloc {
    void *ctx;
    struct alloc_vtable *vtable;
};

struct alloc_vtable {
    void *(*alloc)(void *ctx, usize size, usize alignment);
    void *(*resize)(void *ctx, void *ptr, usize size, usize alignment);
    void *(*free)(void *ctx, void *ptr);
};

void *alloc_mem(struct alloc *allocator);
void *alloc_zero(struct alloc *allocator);
void *alloc_aligned(struct alloc *allocator, usize alignment);
void *alloc_aligned_zero(struct alloc *allocator, usize alignment);

void *alloc_resize(struct alloc *allocator, void *ptr, usize new_size);
void *alloc_resize_aligned(struct alloc *allocator, void *ptr, usize new_size,
    usize alignment);

void alloc_free(struct alloc *allocator, void *ptr);

#endif
