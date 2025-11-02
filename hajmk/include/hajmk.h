#ifndef HAJMK_H
#define HAJMK_H

#include <sys/cdefs.h>

#define project(name, b) \
    static void hajmk_##name(struct build *b); \
    static const struct project_info hajmk_desc_##name \
    __section("hajmk_projects") = { \
        .project_name = #name, \
        .fn = hajmk_##name\
    };\
    static void hajmk_##name(struct build *b)

struct build;
struct target;
struct project;
struct library;

struct project_info {
    const char *project_name;
    void (*fn)(struct build *b);
};

struct target *library(struct build *b, const char *name);
struct target *executable(struct build *b, const char *name);

struct project *get_project(struct build *b, const char *name);
struct library *project_get_library(struct project *p, const char *name);

struct library *find_library(struct build *b, const char *name);

void add_sources(struct target *t, ...);
void add_cflags(struct target *t, ...);
void add_ldlags(struct target *t, ...);
void add_includes(struct target *t, ...);

void link_with(struct target *t, struct library *lib);

#endif
