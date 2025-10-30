#ifndef VEC_H
#define VEC_H
#include <alloc.h>

/* Implementation of a non-generic vector type. This data structure is not thread-safe and should only be dynamically allocated, using vec_new. */
struct vec {
    struct alloc* allocator;
    void* elements;
    int capacity;
    int size;
    int element_size;
};

/* Creates a new non-generic vector with the specified allocator and element size */
struct vec* vec_new(struct alloc* allocator, int element_size);
/*
Destroys the given vector and frees it from memory.
libstd makes no attempt to cleanup any dynamically allocated memory pointed to by ANY element within the vector.
Please make sure you have properly run the associated elements' destructors (if any) before running this.
*/
void vec_destroy(struct vec* obj);
/* Gets the size (number of elements) within the given vector */
int vec_size(struct vec* obj);
/* Gets the capacity (total number of elements allowed within the current allocation) within the given vector */
int vec_capacity(struct vec* obj);
/*
Pushes an element into the end of a vector.
The element pointed to must match the element size specified.
libstd makes no attempt to distinguish the difference between types.
For example, a vector with an element size of 8 could contain elements that are a binary blob of 8 bytes, a u64, etc.
The element pointed to will be copied to the vector.
*/
void vec_push(struct vec* obj, void* element);
/*
Removes an element at the specified location within a vector.
libstd makes no attempt to cleanup any dynamically allocated memory pointed to by the element you erase.
Please make sure you have properly run the associated element's destructor (if any) before running this.
*/
void vec_remove(struct vec* obj, int at);
/*
Removes an element from the end of a vector.
libstd makes no attempt to cleanup any dynamically allocated memory pointed to by the element you erase.
Please make sure you have properly run the associated element's destructor (if any) before running this.
*/
void vec_pop(struct vec* obj);
/*
Returns a pointer to the associated item at the specified index within the given vector.
Will return NULL if the index is out of bounds.
*/
void* vec_at(struct vec* obj, int at);
/*
Returns a pointer to the first item within the given vector.
Will return NULL if the vector is empty.
*/
void* vec_first(struct vec* obj);
/*
Returns a pointer to the last item within the given vector.
Will return NULL if the vector is empty.
*/
void* vec_last(struct vec* obj);

#endif
