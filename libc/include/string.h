#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void *memcpy(void *dst, const void *src, usize n);
void *rmemcpy(void *dst, const void *src, usize n);
void *memmove(void *dst, const void *src, usize n);
void *memset(void *s, int v, usize n);
void *memchr(const void *s, int c, usize n);
void *memrchr(void *s, int c, long n);
int memcmp(const void *s1, const void *s2, usize n);

char *strchr(const char *s, int c);
char *strrchr(const char *s, int ch);
char *strchrnul(const char *s, int ch, usize n);
usize strlen(const char *s);
usize strnlen(const char *s, usize n);
int strcmp(const char *s1, const char *s2);
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

/* BSD related string function */
usize strlcpy(char *dst, const char *src, usize dstsize);
usize strlcat(char *dst, const char *src, usize dstsize);

/* libisoc */
char *strcat(char *d, const char *s);
char *strncat(char *d, const char *s, usize n);
char *strcpy(char *dst, const char *src);
char *strncpy(char *d, const char *s, usize n);
char *strtok(char *s, const char *delim);
char *strtok_r(char *str, const char *delim, char **saveptr);
char *strdup(const char *s);
char *strndup(const char *s, usize n);

#endif
