#ifndef TREE_H
#define TREE_H
#include <alloc.h>
#include <stdint.h>

/* implementation of a red-black tree */

enum tree_node_color {
    RED,
    BLACK,
};

struct tree_node {
    union {
        struct {
            struct tree_node *left, *right;
        };
        struct tree_node* child[2];
    };
    struct tree_node* parent;
    enum tree_node_color color;
    /* the key */
};

struct tree {
    struct alloc* alloc;
    struct tree_node* root;
    u32 key_size;
};

void tree_init(struct tree* tree, struct alloc* alloc, u32 key_size);

#endif