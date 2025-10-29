#include <stdio.h>
#include <stdalign.h>

int main()
{
    int out = print("I love my {x}\n", 0xbabe);
    return 0;
}
