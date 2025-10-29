#include <stdio.h>
#include <stdalign.h>

int main()
{
    print("Alignment of align_max_t: {d}\n", alignof(max_align_t));
    return 0;
}
