#ifndef VEC_H
#define VEC_H

#include <alloc.h>
#include <slice.h>
#include <stdint.h>
#include <stdalign.h>

struct vec {
    struct alloc* alloc;
    struct slice items; /* data + len */
    usize cap;
    /* item unlikely be that big */
    u32 item_size, alignment;
};

#define vec_init_typed(vec, alloc, type) vec_init_aligned(vec, alloc, \
    sizeof(type), alignof(type))

#define vec_get_typed(v, i, t) (*(t*) vec_get(v, i))

#define vec_foreach_typed(v, i, n, t)                          \
    for (usize i = 0;                                          \
         i < (v)->items.len && vec_get_into(v, i, &n) != null; \
         i++)

// #define vec_foreach_typed(v, i, n, t)            \
//     for (usize i = 0, t n = vec_get_typed(v, t, 0); \
//          i < v->items.len; n = vec_get_typed(v, i++, t))

void vec_init(struct vec *vec, struct alloc* alloc, usize item_size);
void vec_init_aligned(struct vec *vec, struct alloc *alloc, usize item_size,
    usize alignment);
void vec_free(struct vec *vec);

void vec_push(struct vec *vec, void *item);
void vec_insert(struct vec *vec, usize at, void *item);
void vec_fill(struct vec *vec, void *item);
void vec_rotate(struct vec *vec, isize rotation);

void *vec_front(struct vec* vec);
void *vec_back(struct vec* vec);
void *vec_get(struct vec *vec, usize at);
void *vec_get_into(struct vec *vec, usize at, void *addr);

void vec_pop(struct vec *vec);
void vec_remove(struct vec *vec, usize at);

void vec_reserve(struct vec *vec, usize capacity);

#endif
