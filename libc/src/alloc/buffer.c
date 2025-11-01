#include <alloc/buffer.h>
#include <stdalign.h>

static void *alloc(void *ctx, usize size, usize alignment);
static void *resize(void *ctx, void *ptr, usize size, usize alignment);

static struct alloc_vtable vtable = {
    .alloc = alloc,
    .resize = resize,
    .free = null,
};

struct alloc buffer_alloc_init(struct buffer_alloc *buf, u8 *buffer,
    usize size)
{
    buf->buffer = buffer;
    buf->size = size;
    buf->pos = 0;
    buf->last = null;
    buf->last_size = 0;

    return (struct alloc) {
        .ctx = buf,
        .vtable = &vtable,
    };
}

static void *alloc(void *ctx, usize size, usize alignment)
{
    struct buffer_alloc *self = ctx;
    void *next = align_forward(self->buffer + self->pos, alignment);

    if ((u8*) next > self->buffer + self->size) return null;

    self->last = next;
    self->last_size = size;
    self->pos = (ptrdiff_t) next - (ptrdiff_t) self->buffer + size;

    return next;
}

static void *resize(void *ctx, void *ptr, usize size, usize alignment)
{
    struct buffer_alloc *self = ctx;

    if (self->last == ptr) {
        if ((u8*) self->last + size > self->buffer + self->size) return null;

        usize off = size - self->last_size;
        self->last_size = size;
        self->pos += off;

        return ptr;
    }

    return alloc(ctx, size, alignment);
}
