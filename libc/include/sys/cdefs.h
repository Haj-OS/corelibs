#ifndef SYS_CDEFS_H
#define SYS_CDEFS_H

#define __HajOS__

#define __unused __attribute__((__unused__))
#define __used __attribute__((__used__))
#define __section(x) __attribute__((section(x)))
#define __aligned(x) __attribute__((aligned(x)))
#define __packed __attribute__((packed))
#define __dead __attribute__((noreturn))

#endif
