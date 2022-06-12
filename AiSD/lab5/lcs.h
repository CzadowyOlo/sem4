#ifndef LCS_H
#define LCS_H

#include <stddef.h>

void lcs_lenght(const unsigned *X,  const unsigned *Y, size_t m, size_t n, unsigned **b, unsigned **c);
void print_lcs_help(const unsigned *X, size_t m, size_t n, unsigned **b, size_t i, size_t j);
void print_lcs(const unsigned *X, size_t m, size_t n, unsigned **b);
void print_array(unsigned *tab, size_t n);

#endif
