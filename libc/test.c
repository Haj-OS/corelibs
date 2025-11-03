#include <stdio.h>
#include <stdalign.h>
#include <alloc/buffer.h>

int main()
{
    print("{p}\n", 0xFFFFFFFFFFFFFFFF);
    return 0;
}
