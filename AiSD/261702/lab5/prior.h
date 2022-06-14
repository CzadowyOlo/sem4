#ifndef PRIOR_H
#define PRIOR_H

#include <stddef.h>


#define swap(a, b) \
(a = a ^ b),    \
(b = a ^ b),    \
(a = b ^ a)


static inline size_t parent_i (size_t i);
static inline size_t left_i (size_t i);
static inline size_t right_i (size_t i);
void max_heapify(unsigned array[], size_t i, size_t heapsize);
unsigned heap_maximum(unsigned array[]);
unsigned heap_extract_max(unsigned array[], size_t heapsize);
void heap_increase_key(unsigned array[], size_t i, unsigned key);
void max_heap_insert(unsigned array[], unsigned key, size_t heapsize);
void print_array(unsigned tab[], size_t n);
void print_HEAP(unsigned array[], size_t current, int depth, char prefix, size_t n);
void fill_traces(size_t n);
void print_heap(unsigned array[], size_t n);

#endif
