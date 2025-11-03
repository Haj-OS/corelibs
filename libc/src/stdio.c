#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#ifdef BUFSIZ
#undef BUFSIZ
#define BUFSIZ 1024
#endif

enum buf_flags {
    FLUSHABLE = 1 << 0,
    RESIZABLE = 1 << 1,
};

struct buf {
    void *ctx;
    int fd, offset, flags, size;
    char *data;
};

static char stdout_buf[BUFSIZ];
static char stderr_buf[BUFSIZ];

static struct buf outbuf = {
    .ctx = null,
    .fd = STDOUT_FILENO,
    .flags = FLUSHABLE,
    .offset = 0,
    .size = BUFSIZ,
    .data = stdout_buf,
};

static struct buf errbuf = {
    .ctx = null,
    .fd = STDERR_FILENO,
    .flags = FLUSHABLE,
    .offset = 0,
    .size = BUFSIZ,
    .data = stderr_buf,
};

static struct buf *current = null;

/* returns null when ran out of space */
static const char* handle_fmt(const char *fmt, int *wrote, va_list list);
/* returns 0 when ran out of space */
static int print_num(int64_t num, char mode);
static int print_str(const char *str, int optional_len);
/* return false when ran out of space */
static bool putc(char c);
static bool flush_current();
static i64 load_num(char size, va_list list);


int print(const char *fmt, ...)
{
    va_list l;
    va_start(l, fmt);
    int n = vprint(fmt, l);
    va_end(l);

    return n;
}

int vprint(const char *fmt, va_list list)
{
    return vfprint(STDOUT_FILENO, fmt, list);
}

int fprint(int fd, const char *fmt, ...)
{
    va_list l;
    va_start(l, fmt);
    int n = vfprint(fd, fmt, l);
    va_end(l);

    return n;
}

int vfprint(int fd, const char *fmt, va_list list)
{
    char tmp_buf[BUFSIZ];
    bool flush = false;
    struct buf tmp = { 0 };

    if (fd == STDOUT_FILENO) {
        current = &outbuf;
    } else if (fd == STDERR_FILENO) {
        current = &errbuf;
    } else if (fd > 0) {
        tmp.fd = fd;
        tmp.size = BUFSIZ;
        tmp.data = tmp_buf;
        tmp.flags = FLUSHABLE;
        current = &tmp;
        flush = true;
    }

    int wrote = 0;
    char c;

    for (; (c = *fmt); fmt++, wrote++) {
        if (c == '{') {
            fmt++;
            const char *test = handle_fmt(fmt, &wrote, list);
            if (test == null)
                return wrote;
            fmt = test;
            continue;
        }

        if (!putc(c))
            return wrote;
    }

    if (flush)
        flush_current();

    current = null;

    return wrote;
}

int sprint(char *buf, usize size, const char *fmt, ...)
{
    va_list l;
    va_start(l, fmt);
    int n = vsprint(buf, size, fmt, l);
    va_end(l);

    return n;
}

int vsprint(char *buf, usize size, const char *fmt, va_list list)
{
    struct buf tmp = {
        .ctx = null,
        .fd = -1,
        .flags = 0,
        .offset = 0,
        .size = size - 1,
        .data = buf,
    };

    current = &tmp;

    int n = vfprint(tmp.fd, fmt, list);
    buf[n] = 0;

    return n;
}

int aprint(struct alloc *allocator, const char *fmt, ...)
{
    va_list l;
    va_start(l, fmt);
    int n = vaprint(allocator, fmt, l);
    va_end(l);

    return n;
}

int vaprint(struct alloc *allocator, const char *fmt, va_list list)
{
    struct buf tmp = {
        .ctx = null,
        .fd = -1,
        .flags = 0,
        .offset = 0,
        .size = BUFSIZ,
        .data = alloc_aligned(allocator, BUFSIZ, alignof(char)),
    };

    if (tmp.data == null) return 0;

    current = &tmp;

    return vfprint(tmp.fd, fmt, list);
}

static const char* handle_fmt(const char *fmt, int *wrote, va_list list)
{
    /* ignore empty */
    if (fmt[0] == '}')
        return fmt;

    char size_mod = 'w';

    /* expect s */
    if (fmt[0] == '*') {
        if (fmt[1] != 's')
            return NULL;

        int len = va_arg(list, int);
        int test = print_str(va_arg(list, char*), len);
        if (test == 0)
            return NULL;
        
        *wrote += test;
        fmt += 2;
        return fmt;
    }

    /* size modifier */
    if (fmt[1] != '}') {
        size_mod = *fmt++;
        switch (size_mod) {
        case 'b':
        case 'h':
        case 'w':
        case 'q':
            break;
        default:
            return NULL;
        }
    }

    switch (fmt[0]) {
    case 'd':
    case 'u':
    case 'b':
    case 'o':
    case 'x':
    case 'X':
    {
        char mode = *fmt++;
        i64 num = load_num(size_mod, list);
        int test = print_num(num, mode);
        if (test == 0)
            return null;
        *wrote += test - 1;
    }
    }

    return fmt;
}

static int print_num(i64 num, char mode)
{
    char tmp[64] = { 0 };
    char *iter = tmp + 63;
    int wrote = 0;
    bool sign = false;

    if (num == 0) {
        *iter-- = '0';
        wrote++;
    }

    switch (mode) {
    case 'x':
    case 'X':
    {
        u64 n = num;
        char x_c = mode == 'x' ? 'a' : 'A';

        while (n > 0) {
            int rem = n % 16;
            if (rem < 10)
                *iter-- = '0' + rem;
            else
                *iter-- = x_c + (rem - 10);
            wrote++;
            n /= 16;
        }
        iter++;

        break;
    }
    case 'b':
    {
        u64 n = num;

        while (n > 0) {
            for (int i = 0; i < 8; i++) {
                *iter-- = (n & (1 << i)) ? '1' : '0';
                wrote++;
            }

            n >>= 8;
        }
        iter++;

        break;
    }
    case 'o':
    {
        u64 n = num;

        while (n > 0) {
            *iter-- = '0' + (n % 8);
            wrote++;
            n /= 8;
        }
        iter++;

        break;
    }
    case 'u':
    {
        u64 n = num;

        while (n > 0) {
            *iter-- = '0' + (n % 10);
            wrote++;
            n /= 10;
        }
        iter++;

        break;
    }
    case 'd':
        if (num < 0) {
            sign = true;
            num = -num;
        }

        while (num > 0) {
            *iter-- = '0' + (num % 10);
            wrote++;
            num /= 10;
        }

        if (!sign)
            iter++;
        else {
            *iter = '-';
            wrote++;
        }
        break;
    }

    for (int i = 0; i < wrote; i++) {
        if (!putc(iter[i]))
            return 0;
    }

    return wrote;
}

static int print_str(const char *str, int optional_len)
{
    int i;

    if (str == null)
        str = "(nil)";

    if (optional_len) {
        for (i = 0; i < optional_len && str[i] != 0; i++) {
            if (!putc(str[i]))
                return 0;
        }
    } else {
        for (i = 0; str[i] != 0; i++) {
            if (!putc(str[i]))
                return 0;
        }
    }

    return i;
}

static bool putc(char c)
{
    if (current->offset + 1 == current->size)
        if (!flush_current()) return false;

    current->data[current->offset++] = c;

    if (c == '\n')
        flush_current(); /* attempt flush */

    return true;
}

static bool flush_current()
{
    if (current->flags & FLUSHABLE) {
        write(current->fd, current->data, current->offset);
        current->offset = 0;
        return true;
    } else if (current->flags & RESIZABLE) {
        struct alloc *allocator = current->ctx;
        if (allocator == null) return false;

        current->size *= 2;
        current->data = alloc_resize_aligned(allocator, current->data, current->size,
            alignof(char));
        if (current->data == null) return false;

        return true;
    }

    return false;
}

static i64 load_num(char size, va_list list)
{
    switch (size) {
    case 'b':
        return va_arg(list, i32) & 0xFF;
    case 'h':
        return va_arg(list, i32) & 0xFFFF;
    case 'w':
        return va_arg(list, i32) & 0xFFFFFFFF;
    case 'q':
        return va_arg(list, i64);
    }

    return 0;
}
