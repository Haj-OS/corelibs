#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

struct buf {
    int fd, offset;
    char data[BUFSIZ];
};

static struct buf outbuf = { 0 };
static const char* handle_fmt(const char *fmt, int *wrote, va_list list);
static int print_num(int num, char mode);
static void flush_unless(int new_fd);
static void putc(char c);

int print(const char *fmt, ...)
{
    int wrote = 0;
    char c;
    va_list list;
    va_start(list, fmt);

    flush_unless(0);
    for (; (c = *fmt); fmt++, wrote++) {
        if (c == '{') {
            fmt++;
            fmt = handle_fmt(fmt, &wrote, list);
            continue;
        }

        putc(c);
    }

    va_end(list);

    return wrote;
}

static const char* handle_fmt(const char *fmt, int *wrote, va_list list)
{
    switch (fmt[0]) {
    case 'd':
    case 'b':
    case 'o':
    case 'x':
    {
        char mode = *fmt++;
        int num = va_arg(list, int);
        *wrote += print_num(num, mode) - 1;
        break;
    }
    }
    return fmt;
}

static int print_num(int num, char mode)
{
    char tmp[64] = { 0 };
    char *iter = tmp + 63;
    int wrote = 0;
    bool sign = false;

    switch (mode) {
    case 'x':
    {
        unsigned int n = num;

        while (n > 0) {
            int rem = n % 16;
            if (n < 10)
                *iter-- = '0' + rem;
            else
                *iter-- = 'a' + (rem - 10);
            wrote++;
            n /= 16;
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
        putc(iter[i]);
    }

    return wrote;
}

static void flush_unless(int new_fd)
{
    if (new_fd != outbuf.fd) {
        write(outbuf.fd, outbuf.data, outbuf.offset);
        outbuf.offset = 0;
        outbuf.fd = new_fd;
    }
}

static void putc(char c)
{
    if (outbuf.offset + 1 == BUFSIZ) {
        write(outbuf.fd, outbuf.data, outbuf.offset);
        outbuf.offset = 0;
    }

    outbuf.data[outbuf.offset++] = c;

    if (c == '\n') {
        write(outbuf.fd, outbuf.data, outbuf.offset);
        outbuf.offset = 0;
    }
}
