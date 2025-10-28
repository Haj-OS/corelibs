#include <stdio.h>
#include <string.h>

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
        fprintf(stderr, "gensyscalls: unknown cpu arch: %s\n", argv[1]);
        return 1;
    }

    char path_buf[256];
    snprintf(path_buf, 256, "arch/%s/syscalls.s", argv[1]);

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
}
