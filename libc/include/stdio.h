#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <alloc.h>

#define BUFSIZ 4096

/* Simple print formatting functions, inspired by Zig format syntax:
 * {[*][flag][size modifier]mode}
 *
 * flag:
 * u - unsigned
 *
 * size modifier:
 * b - byte (8 bits)
 * h - half (16 bits)
 * w - word (32 bits)
 * q - quad (64 bits)
 * 
 * modes:
 * d - int
 * b - int (binary)
 * o - int (octal)
 * x - int (hexadecimal)
 * c - char
 * s - string, or {*s}
 * a - slice, optional style (one of d, b, o, x, s) e.g. {ax}, {as}
 * p - pointer
 */
int print(const char *fmt, ...);
int fprint(int fd, const char *fmt, ...);
int sprint(usize size, char buf[static size], const char *fmt, ...);
int aprint(struct alloc *allocator, const char *fmt, ...);

#endif
