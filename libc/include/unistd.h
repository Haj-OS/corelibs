#ifndef UNISTD_H
#define UNISTD_H

#include <stddef.h>

/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input. */
#define	STDOUT_FILENO	1	/* Standard output. */
#define	STDERR_FILENO	2	/* Standard error output. */

typedef signed long ssize_t;

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int close(int fd);

#endif
