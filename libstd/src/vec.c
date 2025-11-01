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

void vec_insert(struct vec *vec, usize at, void *item)
{
    if (at >= vec->size) {
        vec_push(vec, item);
        return;
    }

    if (vec->size * vec->item_size >= vec->items.len) {
        vec->items.len *= 2;
        vec->items.ptr = alloc_resize_aligned(vec->alloc, vec->items.ptr,
            vec->items.len, vec->alignment);
    }

    u8 *ptr = vec->items.ptr;
    rmemcpy(ptr + vec->item_size *(at + 1),
        ptr + vec->item_size * at,
        (vec->size - at) * vec->item_size);

    memcpy(ptr + at * vec->item_size, item, vec->item_size);
    vec->size++;
}

void vec_fill(struct vec *vec, void *item)
{
    if (vec->size * vec->item_size >= vec->items.len)
        return;

    for (usize i = vec->size; i < vec->items.len / vec->item_size; i++) {
        u8 *ptr = vec->items.ptr;
        memcpy(ptr + i * vec->item_size, item, vec->item_size);
    }

    vec->size = vec->items.len / vec->item_size;
}

void vec_rotate(struct vec *vec, isize rotation)
{
    u8 *iter = vec->items.ptr;

    rotation = rotation % vec->size;

    if (rotation < 0) {
        u8 data_buffer[vec->item_size * (-rotation)];
        memcpy(data_buffer, iter, vec->item_size * (-rotation));
        memcpy(iter, iter + (-rotation) * vec->item_size,
            (vec->size - (-rotation)) * vec->item_size);
        memcpy(iter + (vec->size - (-rotation)) * vec->item_size,
            data_buffer, vec->item_size* (-rotation));
    } else if (rotation > 0) {
        u8 data_buffer[vec->item_size * rotation];
        memcpy(data_buffer, iter + (vec->size - rotation) * vec->item_size,
            vec->item_size * rotation);
        rmemcpy(iter + rotation * vec->item_size, iter,
            (vec->size - rotation) * vec->item_size);
        memcpy(iter, data_buffer, vec->item_size * rotation);
    }
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

void vec_pop(struct vec *vec)
{
    if (vec->size == 0)
        return;

    vec->size--;
}

void vec_remove(struct vec *vec, usize at)
{
    if (at >= vec->size - 1) {
        vec_pop(vec);
        return;
    }

    u8 *iter = vec->items.ptr;

    memmove(iter + vec->item_size * at,
        iter + vec->item_size * (at + 1),
        (vec->size - at - 1) * vec->item_size);

    vec->size--;
}

void vec_reserve(struct vec *vec, usize capacity)
{
    usize cap = capacity * vec->item_size;

    if (cap >= vec->items.len)
        return;

    vec->items.len = cap;
    vec->items.ptr = alloc_resize_aligned(vec->alloc, vec->items.ptr,
        vec->items.len, vec->alignment);
}

void vec_shrink_to_fit(struct vec *vec)
{
    vec->items.len = vec->size * vec->item_size;
    vec->items.ptr = alloc_resize_aligned(vec->alloc, vec->items.ptr,
        vec->items.len, vec->alignment);
}
