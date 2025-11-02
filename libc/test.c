#include <stdio.h>
#include <stdalign.h>
#include <alloc/buffer.h>

int main()
{
    char buffer[32];
    sprint(buffer, 32, "{x} + {x} = {x}\n", 0xFF, 0xFF, 0xFF + 0xFF);
    print(buffer);

    return 0;
}
