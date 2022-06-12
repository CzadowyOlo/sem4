#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lcs.h"

static size_t comp = 0;
static size_t shift = 0;

void lcs_lenght(const unsigned *X,  const unsigned *Y, size_t m, size_t n, unsigned **b, unsigned **c){

    for (size_t i = 1; i <= m; i++){
        c[i][0] = 0; 
        shift++; 
    }
    for (size_t j = 0; j <= n; j++){
        c[0][j] = 0;
        shift++;
    }
    for (size_t i = 1; i <= m; i++){
        for (size_t j = 1; j <= n; j++){
            if (X[i-1] == Y[j-1]) {
                comp++;
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 0; /* strzałka w lewo-góra */ 
                shift+=2;
            }
            else if (c[i-1][j] >= c[i][j-1]) {
                comp+=2;
                c[i][j] = c[i-1][j];
                b[i][j] = 1; /* stzałka w góre */ 
                shift+=2;
            }
            else {
                comp+=2;
                c[i][j] = c[i][j-1];
                b[i][j] = 2; /* stzałka w lewo */ 
                shift+=2;
            }
        }
    }
}

void print_lcs_help(const unsigned *X, size_t m, size_t n, unsigned **b, size_t i, size_t j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == 0) {
        print_lcs_help(X, m, n, b, i-1, j-1);
        printf("%u ", X[i-1]);
    }
    else if (b[i][j] == 1)
        print_lcs_help(X, m, n, b, i-1, j);
    else
        print_lcs_help(X, m, n, b, i, j-1);
    
}

void print_lcs(const unsigned *X, size_t m, size_t n, unsigned **b) {
    printf("{ ");
    print_lcs_help(X,m,n,b,m,n);
    printf("}\n");
}

void print_array(unsigned *tab, size_t n){
    if( n >= 1){

    printf(" {");
    for (size_t i = 0; i < n - 1; i++){
        printf("%d, ", tab[i]);
    }    

    printf("%d }\n", tab[n-1]);
    }
}

int main(void){

    size_t n;

    unsigned k;
    scanf("%zu", &n);
    //printf("n = %zu \n", n);

    unsigned *X = malloc(sizeof(unsigned) * n);
    unsigned *Y = malloc(sizeof(unsigned) * n);
    

    for(size_t i = 0; i < n; i++){
        scanf("%u", &k);
        X[i] = k;
    }
    for(size_t i = 0; i < n; i++){
        scanf("%u", &k);
        Y[i] = k;
    }


    // unsigned b[n+1][n+1];
    // unsigned c[n+1][n+1];

    unsigned **b = malloc(sizeof(unsigned*) * (n + 1)); 
    unsigned **c = malloc(sizeof(unsigned*) * (n + 1)); 

    for (size_t i = 0; i < n + 1; i++){
        b[i] = malloc(sizeof(int) * (n+1));
    }

    for (size_t i = 0; i < n + 1; i++){
        c[i] = malloc(sizeof(int) * (n+1));
    }


    lcs_lenght(X,Y,n,n,b,c);

    

    if(n < 50){
        printf("kolejno tablice X i Y: \n");
        print_array(X, n);
        print_array(Y, n);
        printf("\n wspólny podciąg: \n");
        print_lcs(X,n,n,b);
    }

    //printf("\n Długość LCS to %u\n \n", odp);
    printf("%zu, %zu, %zu \n", n, comp, shift);


    for(size_t i = 0; i < n + 1; i++){
        free(b[i]);
    }
    free(b);

    for(size_t i = 0; i < n + 1; i++){
        free(c[i]);
    }
    free(c);

    free(X);
    free(Y);
    
    return EXIT_SUCCESS;
}
