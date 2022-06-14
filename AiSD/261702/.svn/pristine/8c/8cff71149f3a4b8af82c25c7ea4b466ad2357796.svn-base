// Binary Search Tree operations in C

#include <stddef.h>



struct node{
    int key;
    char pad[4];
    struct node *left;
    struct node *right;
};


struct node *newNode(int item);
void inorder(struct node *root);
struct node *insert(struct node *node, int key);
struct node *minValueNode(struct node *node);
struct node *deleteNode(struct node *root, int key, struct node *parrent);
void free_subtree(struct node** root);
void print_BST( struct node * root, int depth, char prefix);
double tree_height(struct node* root);
