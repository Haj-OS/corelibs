#include <stdio.h>
#include <stdalign.h>
#include <alloc/buffer.h>

int main()
{
    char buffer[32];
    sprint(buffer, 32, "Hello, {s}!\n", "World");
    print(buffer);

    return 0;
}
