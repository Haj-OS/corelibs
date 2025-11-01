#include <stdalign.h>

void *align_forward(void *addr, usize alignment)
{
    u8* ptr = addr;
    return (u8*) ((usize) (ptr + alignment - 1) & ~(alignment - 1));
}

void *align_backward(void *addr, usize alignment)
{
    u8* ptr = addr;
    return (u8*) ((usize) ptr & ~(alignment - 1));
}
