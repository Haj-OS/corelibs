#include <stdio.h>
#include <vec.h>
#include <alloc/buffer.h>

struct foo {
    int a;
    int b;
};

int main()
{
    unsigned char buffer[128];
    struct buffer_alloc ba;
    struct alloc alloc = buffer_alloc_init(&ba, buffer, sizeof(buffer));

    struct vec v;
    vec_init_typed(&v, &alloc, struct foo);

    struct foo a = {
        .a = 4,
        .b = 3
    };

    vec_push(&v, &a);
    a.a = 7;
    a.b = 0;
    vec_push(&v, &a);

    struct foo tmp;
    vec_foreach_typed(&v, i, tmp, struct foo) {
        print("{d} {d}\n", tmp.a, tmp.b);
    }
    return 0;
}
