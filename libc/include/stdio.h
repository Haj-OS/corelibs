#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>
#include <alloc.h>
#include <stdarg.h>

#define BUFSIZ 4096

/* Simple print formatting functions, inspired by Zig format syntax:
 * {[*][size modifier]mode}
 *
 * size modifier:
 * b - byte (8 bits)
 * h - half (16 bits)
 * w - word (32 bits)
 * q - quad (64 bits)
 * 
 * modes:
 * d - int
 * u - unsigned int
 * b - int (binary)
 * o - int (octal)
 * x - int (hexadecimal)
 * c - char
 * s - string, or {*s}
 * a - slice, optional style (one of d, b, o, x, s) e.g. {ax}, {as}
 * p - pointer
 */
int print(const char *fmt, ...);
int vprint(const char *fmt, va_list list);
int fprint(int fd, const char *fmt, ...);
int vfprint(int fd, const char *fmt, va_list list);
int sprint(char *buf, usize size, const char *fmt, ...);
int vsprint(char *buf, usize size, const char *fmt, va_list list);
int aprint(struct alloc *allocator, const char *fmt, ...);
int vaprint(struct alloc *allocator, const char *fmt, va_list list);

#endif
