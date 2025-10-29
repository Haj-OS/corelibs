#ifndef STDINT_H
#define STDINT_H

#include <stddef.h>

#define INT8_MAX    127
#define INT16_MAX   32767
#define INT32_MAX   2147483647
#define INT64_MAX   9223372036854775807LL

#define INT8_MIN    -128
#define INT16_MIN   -32768
#define INT32_MIN   (-INT32_MAX-1)
#define INT64_MIN   (-INT64_MAX-1)

#define UINT8_MAX   255
#define UINT16_MAX  65535
#define UINT32_MAX  4294967295U
#define UINT64_MAX  18446744073709551615ULL

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef unsigned long uint64_t;
typedef signed long int64_t;
typedef int64_t intptr_t;
typedef uint64_t uintptr_t;

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;

typedef size_t usize;
typedef ptrdiff_t isize;

#endif
