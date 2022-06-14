#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

typedef struct Node
{
    int key;                /* wartość węzła        */
    char pad[4];            /* spadingowane bajty   */
    struct Node* left;      /* lewe poddrzewo       */
    struct Node* right;     /* prawe poddrzewo      */
    struct Node* parent;    /* rodzic węzła         */
   
} Node;

#define swap(a, b) \
(a = a ^ b),    \
(b = a ^ b),    \
(a = b ^ a)


static inline size_t parent_i (size_t i);
static inline size_t left_i (size_t i);
static inline size_t right_i (size_t i);
void max_heapify(int array[], size_t i);
void build_max_heap(int array[], size_t n);
void heapsort(int array[], size_t n);
void print_array(int tab[], size_t n);

#endif
