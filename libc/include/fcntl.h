#ifndef FCNTL_H
#define FCNTL_H

#include <sys/types.h>

#define O_RDONLY 00000
#define O_WRONLY 00001
#define O_RDWR 00002
#define O_ACCMODE 00003
#define O_CREAT 00100
#define O_EXCL 00200
#define O_NOCTTY 00400
#define O_TRUNC 01000
#define O_APPEND 02000
#define O_NONBLOCK 04000
#define O_SYNC 0010000
#define O_ASYNC 020000
#define FASYNC 0020000

#define O_DIRECT 0040000
#define O_LARGEFILE 0100000
#define O_DIRECTORY 0200000
#define O_NOFOLLOW 0400000
#define O_CLOEXEC 02000000

#define O_NOATIME 001000000

int open(const char *path, int flags, ... /* mode_t mode */);

#endif
