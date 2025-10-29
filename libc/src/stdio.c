#include <stdio.h>
#include <unistd.h>

struct buf {
    int fd, offset;
    char data[BUFSIZ];
};

static struct buf outbuf = { 0 };
static void flush_unless(int new_fd);
static void putc(char c);

int print(const char *fmt, ...)
{
    int wrote = 0;
    char c;

    flush_unless(0);
    for (; (c = *fmt); fmt++, wrote++) {
        if (c == '{') {
            /* handle format */
            continue;
        }

        putc(c);
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
