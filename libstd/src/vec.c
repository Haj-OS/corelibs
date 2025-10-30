#include <vec.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define CAPACITY_STEP 4

struct vec* vec_new(struct alloc* allocator, int element_size) {
    struct vec* obj = alloc_zero(allocator,sizeof(struct vec));
    if(obj == NULL)
        return NULL;
    obj->allocator = allocator;
    obj->element_size = element_size;
    return obj;
}
void vec_destroy(struct vec* obj) {
    struct alloc* allocator = obj->allocator;
    alloc_free(allocator,obj->elements);
    alloc_free(allocator,obj);    
}
int vec_size(struct vec* obj) {
    return obj->size;
}
int vec_capacity(struct vec* obj) {
    return obj->capacity;
}
void vec_push(struct vec* obj, void* element) {
    if(obj->size > 0 && obj->size % obj->capacity == 0) {
        obj->capacity = (obj->size / CAPACITY_STEP + 1) * CAPACITY_STEP;
        obj->elements = alloc_resize(obj->allocator, obj->elements, obj->capacity * obj->element_size);
    }
    memcpy(vec_at(obj,this->size++),element,obj->element_size);
}
void vec_remove(struct vec* obj, int at) {
    if(at < 0 || at >= obj->size)
        return;
    if(obj->size == 1 || at == obj->size - 1) {
        obj->size--;
        return;
    }
    memmove(vec_at(obj,at+1),vec_at(obj,at),(obj->size-(at+1))*obj->element_size);
    obj->size--;
}
void vec_pop(struct vec* obj) {
    /* Yes, that is actually the implementation... */
    if(obj->size > 0)
        obj->size--;
}
void* vec_at(struct vec* obj, int at) {
    if(at < 0 || at >= obj->size)
        return NULL;
    return (void*)(((usize)obj->elements)+at*obj->element_size);
}
void* vec_first(struct vec* obj) {
    if(obj->size <= 0)
        return NULL;
    return obj->elements;
}
void* vec_last(struct vec* obj) {
    if(obj->size <= 0)
        return NULL;
    return vec_at(obj, obj->size-1);
}