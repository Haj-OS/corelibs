#include <stdio.h>
#include <stdalign.h>
#include <alloc/buffer.h>
#include <slice.h>

int main()
{
    char buf[] = "Hello World!";
    struct slice s = {
        .ptr = buf,
        .len = 12,
    };

    print("{a}\n",  s);
    print("{ad}\n", s);
    print("{au}\n", s); /* the same as just a */
    print("{ab}\n", s);
    print("{ao}\n", s);
    print("{ax}\n", s);
    print("{ac}\n", s);
    print("{as}\n", s);
    print("{aa}\n", s);
    print("{ap}\n", s);
    return 0;
}
