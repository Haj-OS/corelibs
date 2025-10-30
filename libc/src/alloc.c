#include <alloc.h>
#include <stdalign.h>
#include <string.h>

void *alloc_mem(struct alloc *allocator, usize size)
{
    if (allocator->vtable->alloc == null) return null;

    return allocator->vtable->alloc(allocator->ctx, size,
        alignof(max_align_t));
}

void *alloc_zero(struct alloc *allocator, usize size)
{
    void *ptr = alloc_mem(allocator, size);
    if (ptr == null) return null;
    memset(ptr, 0, size);

    return ptr;
}

void *alloc_aligned(struct alloc *allocator, usize size, usize alignment)
{
    if (allocator->vtable->alloc == null) return null;

    return allocator->vtable->alloc(allocator->ctx, size, alignment);
}

void *alloc_aligned_zero(struct alloc *allocator, usize size, usize alignment)
{
    void *ptr = alloc_aligned(allocator, size, alignment);
    if (ptr == null) return null;
    memset(ptr, 0, size);

    return ptr;
}

void *alloc_resize(struct alloc *allocator, void *ptr, usize new_size)
{
    return allocator->vtable->resize(allocator->ctx, ptr, new_size,
        alignof(max_align_t));
}

void *alloc_resize_aligned(struct alloc *allocator, void *ptr, usize new_size,
    usize alignment)
{
    if (allocator->vtable->resize == null) return null;

    return allocator->vtable->resize(allocator->ctx, ptr, new_size,
        alignment);
}

void alloc_free(struct alloc *allocator, void *ptr)
{
    if (allocator->vtable->free == null) return;

    allocator->vtable->free(allocator->ctx, ptr);
}
