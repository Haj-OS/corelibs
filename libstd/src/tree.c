#include <tree.h>
#include <string.h>

/* prototypes for some private tree related functions */
static struct tree_node* rotate_left(struct tree* tree, struct tree_node* node);
static struct tree_node* rotate_right(struct tree* tree, struct tree_node* node);

void tree_init(struct tree* tree, struct alloc* alloc, u32 key_size) {
    tree->alloc = alloc;
    tree->key_size = key_size;
    tree->root = NULL;
}

static struct tree_node* rotate_left(struct tree* tree, struct tree_node* node) {
    struct tree_node* parent = node->parent;
    struct tree_node* root = node->right; /* opposite direction of rotation */
    struct tree_node* child = root->left; /* direction of rotation */

    node->right = child; /* opposite direction of rotation */
    if(child)
        child->parent = node;

    root->left = node; /* direction of rotation */
    root->parent = parent;
    node->parent = root;
    if(parent)
        if(node == parent->right)
            parent->right = root;
        else
            parent->left = root;
    else
        tree->root = root;
    return root;
}
static struct tree_node* rotate_right(struct tree* tree, struct tree_node* node) {
    struct tree_node* parent = node->parent;
    struct tree_node* root = node->left; /* opposite direction of rotation */
    struct tree_node* child = root->right; /* direction of rotation */

    node->left = child; /* opposite direction of rotation */
    if(child)
        child->parent = node;

    root->right = node; /* direction of rotation */
    root->parent = parent;
    node->parent = root;
    if(parent)
        if(node == parent->right)
            parent->right = root;
        else
            parent->left = root;
    else
        tree->root = root;
    return root;
}

