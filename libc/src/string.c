#include <string.h>

void *memset(void *s, int v, usize n)
{
    u8 *ptr = s;
    while (n--) {
        *ptr++ = (u8) v;
    }
    return s;
}

void *memcpy(void *dst, const void *src, size_t n)
{
    u8 *d = dst;
    const u8 *s = src;

    while (n--) {
        *d++ = *s++;
    }

    return dst;
}
