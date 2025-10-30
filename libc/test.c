#include <stdio.h>
#include <stdalign.h>
#include <alloc/buffer.h>

int main()
{
    unsigned char buffer[32];
    struct buffer_alloc ba;
    struct alloc a = buffer_alloc_init(&ba, buffer, 32);

    alloc_aligned(&a, sizeof(int), 4);
    int *arr = alloc_aligned(&a, sizeof(int), 4);
    int *prev = arr;
    print("prev = {d}\n", arr == prev);
    arr = alloc_resize_aligned(&a, arr, sizeof(int) * 2, 4);
    print("new = {d}\n", arr == prev);

    alloc_aligned(&a, sizeof(int), 4);
    arr = alloc_resize_aligned(&a, arr, sizeof(int) * 3, 4);
    print("new = {d}\n", arr == prev);

    print("{d}\n", ba.pos);

    return 0;
}
