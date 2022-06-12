// splay tree

#include <stdio.h>
#include <stdlib.h>
#include "splay.h"


static double comparisions = 0;
static double read_pointers = 0;

// Create a node
struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  read_pointers++;
  return temp;
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

    for(int i=0; i<depth-1; i++){
        if( left_trace[i]== '|' || right_trace[i]=='|' ) {
        //printf("| \n");
        printf("| ");
        } 
        else {
        //printf("  \n");
        printf("  ");
        }
    }
    if( depth>0 ) printf("%c-", prefix);

    printf("[%d]\n", root->key);
    left_trace[depth]=' ';

    if( root->right != NULL ){
        right_trace[depth]='|';
        print_BST(root->right, depth+1, '\\');
    }
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *x)
{
    struct node *y = x->left;
    x->left = y->right;
    y->right = x;
    read_pointers+=3;
    return y;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    x->right = y->left;
    y->left = x;
    read_pointers+=3;
    return y;
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
 
// This function brings the key at root if key is present in tree.
// If key is not present, then it brings the last accessed item at
// root.  This function modifies the tree and returns the new root
struct node *splay(struct node *root, int key)
{
    // Base cases: root is NULL or key is present at root
    read_pointers++;
    comparisions++;
    if (root == NULL || root->key == key)
        return root;
 
    // Key lies in left subtree
    //read_pointers++;
    comparisions++;
    if (root->key > key)
    {
        // Key is not in tree, we are done
        read_pointers++;
        if (root->left == NULL) return root;
 
        // Zig-Zig (Left Left)
        comparisions++;
        if (root->left->key > key)
        {
            // First recursively bring the key as root of left-left
            root->left->left = splay(root->left->left, key);
 
            // Do first rotation for root, second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            comparisions++;
            // First recursively bring the key as root of left-right
            read_pointers++;
            root->left->right = splay(root->left->right, key);
 
            // Do first rotation for root->left
            read_pointers++;
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
 
        // Do second rotation for root
        read_pointers++;
        return (root->left == NULL)? root: rightRotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        read_pointers++;
        if (root->right == NULL) return root;
 
        // Zig-Zag (Right Left)
        comparisions++;
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            read_pointers++;
            root->right->left = splay(root->right->left, key);
 
            // Do first rotation for root->right
            read_pointers++;
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {   comparisions++;
            // Bring the key as root of right-right and do first rotation
            read_pointers++;
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
 
        // Do second rotation for root
        return (root->right == NULL)? root: leftRotate(root);
    }
}

struct node *insert(struct node *root, int k)
{
    // Simple Case: If tree is empty
    read_pointers++;
    if (root == NULL) return newNode(k);
 
    // Bring the closest leaf node to root
    root = splay(root, k);
 
    // If key is already present, then return
    comparisions++;
    if (root->key == k) return root;
 
    // Otherwise allocate memory for new node
    struct node *newnode  = newNode(k);
 
    // If root's key is greater, make root as right child
    // of newnode and copy the left child of root to newnode
    comparisions++;
    if (root->key > k)
    {
        read_pointers+=3;
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
 
    // If root's key is smaller, make root as left child
    // of newnode and copy the right child of root to newnode
    else
    {
        read_pointers+=3;
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }
 
    return newnode; // newnode becomes new root
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


struct node* delete_key(struct node *root, int key)
{
    read_pointers++;
    struct node *temp;
    if (!root)
        return NULL;
      
    // Splay the given key    
    read_pointers++;
    root = splay(root, key);
      
    // If key is not present, then
    // return root
    comparisions++;
    if (key != root->key)
        return root;
          
    // If key is present
    // If left child of root does not exist
    // make root->right as root   
    read_pointers++;
    if (!root->left)
    {   read_pointers+=2;
        temp = root;
        root = root->right;
    }
      
    // Else if left child exits
    else
    {

        temp = root;
  
        /*Note: Since key == root->key,
        so after Splay(key, root->lchild),
        the tree we get will have no right child tree
        and maximum node in left subtree will get splayed*/
        // New root
        read_pointers++;
        root = splay(root->left, key);
          
        // Make right child of previous root  as
        // new root's right child
        read_pointers+=2;
        root->right = temp->right;
    }
      
    // free the previous root node, that is,
    // the node containing the key
    free(temp);
      
    // return root of the new Splay Tree
    return root;
      
}

struct node *search(struct node *root, int key)
{
    return splay(root, key);
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


 
// Driver code
int main() {
  struct node *root = NULL;
  //struct node *parrent = NULL;
  int n, k;
  double height = 0;
  double sum_c = 0;
  double maks_c = 0;
  double sum_r = 0;
  double maks_r = 0;
  double sum_h = 0;
  double maks_h = 0;

  scanf("%d", &n);

  for(int i = 0; i < n; i++){
    scanf("%d", &k);
    root = insert(root, k);

   if(i < 2049 ){
        height = tree_height(root);
    }
    else if(i%50 == 0){
        height = tree_height(root);
    }
    
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
    
    maks_h = height;

    for(int i = 0; i < n; i++){
    scanf("%d", &k);
    root = delete_key(root, k);
    if(i < 2049 ){
        height = tree_height(root);
    }
    else if(i%50 == 0){
        height = tree_height(root);
    }
    
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

  unsigned long mysize = 8;
  //size_t dupa = 2;


    // init traces
  left_trace = (char*)malloc( (sizeof(char) ) * mysize + 1);
  right_trace = (char*)malloc( (sizeof(char) ) * mysize + 1 );
  for(unsigned int i=0; i<=mysize; i++){
    left_trace[i]=' ';
    right_trace[i]=' ';
  }



  double height_avg = sum_h/(2*n);
  double comp_avg = sum_c/(2*n);
  double reads_avg = sum_r/(2*n);

  //printf("size_n,  comp_avg,  comp_maks, reads_avg, reads_maks, h_avg,   h_final   h_maks \n");
  printf("%d, %f, %f, %f, %f, %f, %f, %f \n", n, comp_avg, maks_c, reads_avg, maks_r, height_avg, height, maks_h);


  free(left_trace);
  free(right_trace);
  free_subtree(&root);


}
