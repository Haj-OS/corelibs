#include <hajmk.h>
#include <stddef.h>

project(foo, b) { 
    struct target *lib = library(b, "foo");

    add_includes(lib, "sample/include", null);
    add_sources(lib, "sample/foo.c", null);
    add_cflags(lib, "-Wall", "-Wextra", null);
}

project(bar, b) {
    struct target *exe = executable(b, "bar");
    struct project *foo = get_project(b, "foo");
    struct library *libfoo = project_get_library(foo, "foo");
    struct library *std = find_library(b, "std");

    add_sources(exe, "sample/main.c", null);
    link_with(exe, libfoo);
    link_with(exe, std);
}
