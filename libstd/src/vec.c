#include <string.h>
#include <vec.h>
#include <stdalign.h>

#define INITIAL_SIZE 16

void vec_init(struct vec *vec, struct alloc* alloc, usize item_size)
{
    vec->alloc = alloc;
    vec->alignment = alignof(max_align_t);
    vec->item_size = item_size;
    vec->size = 0;
    vec->items.len = 0;
    vec->items.ptr = null;
}

void vec_init_aligned(struct vec *vec, struct alloc *alloc, usize item_size,
    usize alignment)
{
    vec->alloc = alloc;
    vec->alignment = alignment;
    vec->item_size = item_size;
    vec->size = 0;
    vec->items.len = 0;
    vec->items.ptr = null;
}

void vec_free(struct vec *vec)
{
    alloc_free(vec->alloc, vec->items.ptr);

    /* reset */
    vec_init_aligned(vec, vec->alloc, vec->item_size, vec->alignment);
}

void vec_push(struct vec *vec, void *item)
{
    if (vec->items.len == 0) {
        vec->items.len = INITIAL_SIZE * vec->item_size;
        vec->items.ptr = alloc_aligned(vec->alloc, vec->items.len,
            vec->alignment);
    } else if (vec->size * vec->item_size >= vec->items.len) {
        vec->items.len *= 2;
        vec->items.ptr = alloc_resize_aligned(vec->alloc, vec->items.ptr,
            vec->items.len, vec->alignment);
    }

    if (vec->items.ptr == NULL) return;

    u8 *ptr = vec->items.ptr;
    memcpy(ptr + (vec->size++) * vec->item_size, item, vec->item_size);
}

void *vec_front(struct vec* vec)
{
    if (vec->items.len == 0) return null;

    return vec->items.ptr;
}

void *vec_back(struct vec* vec)
{
    if (vec->items.len == 0) return null;

    u8 *ptr = vec->items.ptr;

    return ptr + ((vec->size - 1) * vec->item_size);
}

void *vec_get(struct vec *vec, usize at)
{
    if (at > vec->items.len) return null;
    u8 *ptr = vec->items.ptr;
    return ptr + (at * vec->item_size);
}

void *vec_get_into(struct vec *vec, usize at, void *addr)
{
    if (at > vec->items.len) return null;
    u8 *ptr = vec->items.ptr;
    memcpy(addr, ptr + (at * vec->item_size), vec->item_size);

    return addr;
}
