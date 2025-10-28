int main(int, char**, char**);

int __libc_start_main(int argc, char **argv, char **env) {
    return main(argc, argv, env);
}
