#include <string.h>

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

void *memset(void *s, int v, usize n)
{
    u8 *ptr = s;
    while (n--) {
        *ptr++ = (u8) v;
    }

    return s;
}

void *memchr(const void *s, int c, usize n)
{
    if (n != 0) {
        const u8 *p = s;

        do {
            if (*p++ == (u8) c)
                return (void *) (p - 1);
        } while (--n != 0);
    }

    return null;
}

void *memrchr(void *s, int c, usize n)
{
    const u8 *cp;

    if (n != 0) {
        cp = (u8*) s + n;
        do {
            if (*(--cp) == (u8) c)
                return (void *) cp;
        } while (--n != 0);
    }
    
    return null;
}

int memcmp(const void *s1, const void *s2, usize n)
{
    if (n != 0) {
        const u8 *p1 = s1, *p2 = s2;

        do {
            if (*p1++ != *p2++)
                return *--p1 - *--p2;
        } while (--n != 0);
    }
    return 0;
}

char *strchr(const char *s, int ch)
{
    for (;; ++s) {
        if (*s == (char) ch)
            return (char *) s;
        if (!*s)
            return (char *) NULL;
    }
    /* NOTREACHED */
}

char *strrchr(const char *s, int ch)
{
    char *save;

    for (save = NULL;; ++s) {
        if (*s == (char) ch)
            save = (char *) s;
        if (!*s)
            return save;
    }
    /* NOTREACHED */
}

char *strchrnul(const char *s, int ch, usize n)
{
    for (;*s; ++s) {
        if (*s == (char) ch)
            return (char *) s;
    }

    return (char *) s;
}

usize strlen(const char *s)
{
    usize n = 0;

    for (;*s; n++, s++);

    return n;
}

usize strnlen(const char *s, usize n)
{
    const char *cp;
    usize c = 0;

    for (cp = s; n != 0 && *cp != '\0'; cp++, n--, c++);

    return c;
}

int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return 0;

	return *(u8*)s1 - *(u8*) --s2;
}

int strncmp(const char *s1, const char *s2, usize n);
char *stpcpy(char *dst, const char *srt);
usize strspn(const char *s, const char *accept);
usize strcspn(const char *s, const char *reject);

char *strpbrk(const char *s, const char *accept);
char *strsep(char **stringp, const char *delim);

char *strstr(const char *s, const char *r);
char *strcasestr(const char *haystack, const char *needle);
char *strerror(int errnum);
char *strrev(char *s);

usize strlcpy(char *dst, const char *src, usize dstsize);
usize strlcat(char *dst, const char *src, usize dstsize);
