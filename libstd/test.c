#include <stdio.h>
#include <vec.h>
#include <alloc/buffer.h>

int main()
{
    unsigned char buffer[128];
    struct buffer_alloc ba;
    struct alloc alloc = buffer_alloc_init(&ba, buffer, sizeof(buffer));

    struct vec v;
    vec_init_typed(&v, &alloc, int);

    int a;

    a = 7;
    vec_push(&v, &a);
    a = 3;
    vec_push(&v, &a);
    a = 4;
    vec_insert(&v, 1, &a);
    a = 69;
    vec_fill(&v, &a);

    vec_pop(&v);
    vec_remove(&v, 4);
    vec_remove(&v, 13);

    vec_rotate(&v, -11);
    vec_shrink_to_fit(&v);

    int tmp;
    vec_foreach_typed(&v, i, tmp, struct foo) {
        print("{d}\n", tmp);
    }

    print("{d} {d}\n", v.size,  v.items.len / v.item_size);
    return 0;
}
