#include <list.h>
#include <string.h>

void list_init(struct list *list, struct alloc* alloc, usize item_size) {
    list->head = NULL;
    list->tail = NULL;
    list->alloc = alloc;
    list->item_size = item_size;
}
void list_free(struct list* list) {
    struct list_node* idx = list->head;
    while(idx != NULL) {
        struct list_node* next = idx->next;
        alloc_free(list->alloc,idx);
        idx = next;
    }
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}

struct list_node* list_push(struct list* list, void* data) {
    struct list_node* node = alloc_zero(list->alloc, sizeof(struct list_node)-sizeof(char)+list->item_size);
    memcpy(&node->data,data,list->item_size);
    node->prev = list->tail;
    if(list->tail != NULL)
        list->tail->next = node;
    list->tail = node;
    if(list->head == NULL)
        list->head = list->tail;
    list->size++;
    return node;
}
struct list_node* list_prepend(struct list* list, void* data) {
    struct list_node* node = alloc_zero(list->alloc, sizeof(struct list_node)-sizeof(char)+list->item_size);
    memcpy(&node->data,data,list->item_size);
    node->next = list->head;
    if(list->head != NULL)
        list->head->prev = node;
    list->head = node;
    if(list->tail == NULL)
        list->tail = list->head;
    list->size++;
    return node;
}
void list_remove(struct list* list, struct list_node* at) {
    if(list->head == at)
        list->head = at->next;
    if(list->tail == at)
        list->tail = at->prev;
    if(at->prev)
        at->prev->next = at->next;
    if(at->next)
        at->next->prev = at->prev;
    alloc_free(list->alloc,at);
    list->size--;
}

struct list_node* list_front(struct list* list) {
    return list->head;
}
struct list_node* list_back(struct list* list) {
    return list->tail;
}
struct list_node* list_get(struct list* list, usize at) {
    /* find the most optimal path to retrieve an item */
    if(at >= list->size/2)
        return list_get_back(list,at);
    else
        return list_get_front(list,at);
}
struct list_node* list_get_front(struct list* list, usize at) {
    if(at == 0)
        return list->head;
    struct list_node* idx = list->head;
    for(int i=0; i < at && idx != NULL; i++)
        idx = idx->next;
    return idx;
}
struct list_node* list_get_back(struct list* list, usize at) {
    if(at == list->size-1)
        return list->tail;
    struct list_node* idx = list->tail;
    for(int i=0; i < list->size-at && idx != NULL; i++)
        idx = idx->prev;
    return idx;
}