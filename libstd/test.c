#include <stdio.h>
#include <vec.h>

struct foo {
    int a;
    int b;
};

int main()
{
    struct vec v;
    vec_init_typed(&v, null, struct foo);
    int out = print("sizeof = {d}, alignof = {d}\n", v.item_size, v.alignment);

    struct foo tmp;
    vec_foreach_typed(&v, i, tmp, struct foo) {
        print("{d} {d}\n", tmp.a, tmp.b);
    }
    return 0;
}
