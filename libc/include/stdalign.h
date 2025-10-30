#ifndef STDALIGN_H
#define STDALIGN_H

#include <stdint.h>

#define alignas _Alignas
#define alignof _Alignof

typedef struct { long long __ll; long double __ld; } max_align_t;

void *align_forward(void *addr, usize alignment);
void *align_backward(void *addr, usize alignment);

#endif
