#ifndef STDDEF_H
#define STDDEF_H

typedef unsigned long size_t;
typedef signed long ptrdiff_t;

#define NULL                    ((void*) 0)
#define offsetof(type, field)   ((size_t) (&((type *) 0)->field))

#endif
