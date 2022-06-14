// Binary Search Tree operations in C

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

static double comparisions = 0;
static double read_pointers = 0;

static double curr_height = 0;
static double maks_height = 0;
// TODO: 
// search
// min/maks
// insert
// delete

// Jako miary złożoności zliczaj: 

// liczby porównań między kluczami, ez

// liczby odczytów i podstawień wskaźników łączących elementy struktury drzewa, // ??

// wysokość drzewa po każdej operacji.


// Create a node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  read_pointers++;
  return temp;
}

double tree_height(struct node* root)
{
    if (root == NULL)
    {
       return -1;
    }
    else
    {
        // compute the depth of each subtree 
        double lDepth = tree_height(root->left);
        double rDepth = tree_height(root->right);
 
        // use the larger one
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    printf("%d -> ", root->key);

    // Traverse right
    inorder(root->right);
  }
}

// Insert a node
struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  comparisions++;
  if (node == NULL){
    curr_height++;
    return newNode(key);
  } 

  // Traverse to the right place and insert the node
  comparisions++;
  curr_height++;
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
    struct node *current = node;

    // Find the leftmost leaf
    read_pointers+=2;
    while (current && current->left != NULL){
      read_pointers+=3;
      current = current->left;
    }
    

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key, struct node *parrent) {
  
  // Return if the tree is empty
  read_pointers++;
  if (root == NULL) return root;

  // Find the node to be deleted
  comparisions++;
  if (key < root->key){
    parrent = root;
    root->left = deleteNode(root->left, key, parrent);
  }
  else if (key > root->key){
    //parrent = root;
    root->right = deleteNode(root->right, key, parrent);
  }
  else {
    // If the node is with only one child or no child
    
    read_pointers++;
    if (root->left == NULL) {
      read_pointers++;
      struct node *temp = root->right;
      free(root);
      // if(parrent != NULL){
      //   printf("parent of deleted node: %d \n", parrent->key);
      // }
      return temp;
    } 
    else if (root->right == NULL) {
      read_pointers+=2;
      struct node *temp = root->left;
      free(root);
      // if(parrent != NULL){
      //   printf("parent of deleted node: %d \n", parrent->key);
      // }
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    read_pointers++;
    root->key = temp->key;

    // Delete the inorder successor
    
    // if(parrent != NULL){
    //   printf("parent of deleted node: %d \n", parrent->key);
    // }
    
    // parrent = root;
    root->right = deleteNode(root->right, temp->key, parrent);
  }
  
  return root;
}

void free_subtree(struct node** root){
  if( *root == NULL ) return;
  if( (*root)->left != NULL ){
    free_subtree( &(*root)->left );
  }
  if( (*root)->right != NULL ){
    free_subtree( &(*root)->right );
  }
  free(*root);
  *root=NULL;  
}

// global variables used in `print_BST`
static char* left_trace; // needs to be allocaded with mysize
static char* right_trace; // needs to be allocaded with mysize


void print_BST( struct node * root, int depth, char prefix){
  if( root == NULL ) return;
  if( root->left != NULL ){
    print_BST(root->left, depth+1, '/');
  }
  if(prefix == '/') left_trace[depth-1]='|';
  if(prefix == '\\') right_trace[depth-1]=' ';
  if( depth==0) printf("-");
  if( depth>0) printf(" ");
  for(int i=0; i<depth-1; i++)
    if( left_trace[i]== '|' || right_trace[i]=='|' ) {
      //printf("| \n");
      printf("| ");
    } else {
      //printf("  \n");
      printf("  ");
    }
  if( depth>0 ) printf("%c-", prefix);
  printf("[%d]\n", root->key);
  left_trace[depth]=' ';
  if( root->right != NULL ){
    right_trace[depth]='|';
    print_BST(root->right, depth+1, '\\');
  }
}


// Driver code
int main() {
  struct node *root = NULL;
  struct node *parrent = NULL;
  int n, k;
  double height = 0;
  double sum_c = 0;
  double maks_c = 0;
  double sum_r = 0;
  double maks_r = 0;
  double sum_h = 0;
  double maks_h = 0;

  // root = insert(root, 8);
  // root = insert(root, 3);
  // root = insert(root, 1);
  // root = insert(root, 6);
  // root = insert(root, 7);
  // root = insert(root, 10);
  // root = insert(root, 14);
  // root = insert(root, 4);

  

  scanf("%d", &n);

  unsigned long mysize = n;
  //size_t dupa = 2;


    // init traces
  left_trace = (char*)malloc( (sizeof(char) ) * mysize + 1);
  right_trace = (char*)malloc( (sizeof(char) ) * mysize + 1 );
  for(unsigned int i=0; i<=mysize; i++){
    left_trace[i]=' ';
    right_trace[i]=' ';
  }
  printf("inserting: \n");
  for(int i = 0; i < n; i++){
    scanf("%d", &k);
    root = insert(root, k);
    printf("\n");
    print_BST(root, 0, '-');
    printf("\n");
    //height = tree_height(root);
    if(comparisions >= maks_c) maks_c = comparisions;
    if(read_pointers >= maks_r) maks_r = read_pointers;
    if(curr_height >= maks_height) maks_height = curr_height;
    sum_c+= comparisions;
    sum_r+= read_pointers;
    sum_h+= maks_height;
    

    //printf("%d, %d, %d, %d \n", n, comparisions, read_pointers, height );
    curr_height = 0;
    comparisions = 0;
    read_pointers = 0;
  }
    
    maks_h = maks_height;
    printf("deleting: \n");
    for(int i = 0; i < n; i++){
    scanf("%d", &k);
    root = deleteNode(root, k, parrent);
    printf("\n");
    print_BST(root, 0, '-');
    printf("\n");
    height = tree_height(root);
    if(comparisions >= maks_c) maks_c = comparisions;
    if(read_pointers >= maks_r) maks_r = read_pointers;
    //if(curr_height >= maks_height) maks_height = curr_height;
    sum_c+= comparisions;
    sum_r+= read_pointers;
    sum_h+= height;
    

    //printf("%d, %d, %d, %d \n", n, comparisions, read_pointers, height );
    //curr_height = 0;
    comparisions = 0;
    read_pointers = 0;
  }



  // printf("TREE:\n\n");
  // print_BST(root, 0, '-');
  // printf("\n\n");

  // printf("Inorder traversal: ");
  // inorder(root);

  // printf("\nAfter deleting 14\n");
  // root = deleteNode(root, 14, parrent);

  // printf("TREE:\n\n");
  // print_BST(root, 0, '-');
  // printf("\n\n");

  // printf("Inorder traversal: ");
  // inorder(root);
  // printf("\n");

  double height_avg = sum_h/(2*n);
  double comp_avg = sum_c/(2*n);
  double reads_avg = sum_r/(2*n);

  //printf("size_n,  comp_avg,  comp_maks, reads_avg, reads_maks, h_avg,   h_final   h_maks \n");
  printf("%d, %f, %f, %f, %f, %f, %f, %f \n", n, comp_avg, maks_c, reads_avg, maks_r, height_avg, height, maks_height);



  free(left_trace);
  free(right_trace);
  free_subtree(&root);

  //printf("\n sizeof char: %ld \n", sizeof(char));
}
