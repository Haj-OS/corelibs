#ifndef SLICE_H
#define SLICE_H

#include <stdint.h>

struct slice {
    void *ptr;
    usize len;
};

#endif
