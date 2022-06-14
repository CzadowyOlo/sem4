// Splay Tree operations in C

#include <stddef.h>



struct node{
    int key;
    char pad[4];
    struct node *left;
    struct node *right;
};


struct node *newNode(int item);
struct node *rightRotate(struct node *x);
struct node *leftRotate(struct node *x);
struct node *splay(struct node *root, int key);
void free_subtree(struct node** root);
void print_BST( struct node * root, int depth, char prefix);
struct node *deleteNode(struct node *root, int key);
void preOrder(struct node *root);
struct node *insert(struct node *root, int k);
struct node *search(struct node *root, int key);
struct node *minValueNode(struct node *node);
struct node* delete_key(struct node *root, int key);
double tree_height(struct node* root);
