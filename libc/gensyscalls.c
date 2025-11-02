#include <stdio.h>
#include <string.h>
#include <sys/cdefs.h>
#include <unistd.h>

struct syscall {
    const char *name;
    int opcode;
};

static struct syscall table[] = {
    {"read",    0},
    {"write",   1},
    {"exit",    60},
    {0}
};

int main(int argc, char **argv)
{
    if (argc != 2) return 1;

    if (strcmp(argv[1], "x86_64") != 0) {
#ifndef __HajOS__
        fprintf(stderr, "gensyscalls: unknown cpu arch: %s\n", argv[1]);
#else
        fprint(STDERR_FILENO, "gensyscalls: unknown cpu arch: {s}\n", argv[1]);
#endif
        return 1;
    }

    char path_buf[256];
#ifndef __HajOS__
    snprintf(path_buf, 256, "arch/%s/syscalls.s", argv[1]);
#else
    sprint(path_buf, 256, "arch/{s}/syscalls.s", argv[1]);
#endif

#ifndef __HajOS__
    FILE *f = fopen(path_buf, "a");

    struct syscall *iter = table;

    while (iter->name) {
        fprintf(f, ".global %s\n"
                   "%s:\n"
                   "    mov $%d, %%rax\n"
                   "    jmp __syscall\n\n", iter->name, iter->name,
            iter->opcode);
        iter++;
    }

    fclose(f);
#else
#error "No buffered IO yet"
#endif
}
