#ifndef LIST_H
#define LIST_H

#include <alloc.h>
#include <stdint.h>

struct list_node {
    struct list_node *prev, *next;
    char data; /* space of character is not actually used */
};

struct list {
    struct alloc* alloc;
    struct list_node *head, *tail;
    usize size;
    u32 item_size;
};

void list_init(struct list *list, struct alloc* alloc, usize item_size);
void list_free(struct list* list);

struct list_node* list_push(struct list* list, void* data);
struct list_node* list_prepend(struct list* list, void* data);
void list_remove(struct list* list, struct list_node* node);

struct list_node* list_front(struct list* list);
struct list_node* list_back(struct list* list);
struct list_node* list_get(struct list* list, usize at);
struct list_node* list_get_front(struct list* list, usize at);
struct list_node* list_get_back(struct list* list, usize at);

#endif