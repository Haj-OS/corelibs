corelibs
==========
This repository contains the source code of HajOS major libraries, which were
designed in a way to provide a fast, safe and decent experience writing C
programs on/for HajOS

List of provided libraries:
- libc
- libmalloc
- libisoc
- libstd

libc:
A C standard library done a bit differently, libc in HajOS is made to be simple,
lightweight and fast without hidden heap allocations or ambigious APIs provided
by ISO C standard

libmalloc:
C standard malloc implementation, provided as a separate library due to 
complexity of the library, this allows users to opt out or provide their own
malloc implementation

libisoc:
C standard library functions that did not make it into the libc due to their
issues, serves as a compatibility layer when porting projects to HajOS

libstd:
A standard library for the C language providing useful and missing features in
the C language, like data structures and utilities
