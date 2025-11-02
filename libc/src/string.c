#include <string.h>

void *memset(void *s, int v, usize n)
{
    u8 *ptr = s;
    while (n--) {
        *ptr++ = (u8) v;
    }
    return s;
}

void *memcpy(void *dst, const void *src, usize n)
{
    u8 *d = dst;
    const u8 *s = src;

    while (n--) {
        *d++ = *s++;
    }

    return dst;
}

void *rmemcpy(void *dst, const void *src, usize n)
{
    u8 *d = dst;
    const u8 *s = src;

    d += n - 1;
    s += n - 1;

    while (n--) {
        *d-- = *s--;
    }

    return dst;
}

void *memmove(void *dst, const void *src, usize n)
{
    u8 *d = dst;
    const u8 *s = src;

    if (d < s) {
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else if (d > s) {
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

    return dst;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return 0;

	return (*(u8*)s1 - *(u8*)--s2);
}
