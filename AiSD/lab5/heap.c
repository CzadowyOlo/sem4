#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "heap.h"

// TODO: 
// f max-heapify
// f build-max-heap
// f 
static size_t heapsize = 0;
static size_t comp = 0;
static size_t shift = 0;


static inline size_t parent_i (size_t i){ // git
    return (i-1) >> 1;
}

static inline size_t left_i (size_t i){ //git
    return ((i << 1) | 1);
}

static inline size_t right_i (size_t i){ // git
    return (((i+1) << 1));
}

void max_heapify(int *array, size_t i){
    size_t l = left_i(i);
    size_t r = right_i(i);
    size_t largest = 0;

    if (l <= heapsize && array[l] > array[i]){
        largest = l;
        comp+=1;
    }
    else{
        largest = i;
        comp+=1;
    }

    comp+=1;
    if (r <= heapsize && array[r] > array[largest]){
        largest = r;
    }
    if (largest != i){
        swap(array[i], array[largest]);
        shift+=3;
        max_heapify(array, largest);
    }
}


void build_max_heap(int *array, size_t n){
    heapsize = n;
    for (size_t i = n/2; i < __SIZE_MAX__; i--){
        max_heapify(array, i);
    }
}

void heapsort(int *array, size_t n){
    build_max_heap(array, n);
    for (size_t i = n; i >= 1; i--){
        swap(array[0], array[i]);
        shift+=3;
        heapsize--;
        max_heapify(array, 0);
    }
}

void print_array(int *tab, size_t n)
{
    printf(" {");
    for (size_t i = 0; i < n - 1; i++){
        printf("%d, ", tab[i]);
    }    

    printf("%d }\n", tab[n-1]);
}

int main(void){

    //assert(left_i(0) == 1);
    size_t n; // size of array
    float dur = 0.0;
    int k;
    scanf("%zu", &n);

    //int myarray[n]; // array to be rebuild as heap and sorted
    int *myarray = malloc(sizeof(int) * n);


    for (size_t i = 0; i < n; i++){
        scanf("%d", &k);
        myarray[i] = k;
    }

    if(n < 50){
        printf("before sort: \n");
        print_array(myarray, n);
        const clock_t begin_time = clock();
        heapsort(myarray, n-1);
        const clock_t end_time = clock();
    
        dur = (float)(end_time - begin_time) /  CLOCKS_PER_SEC;

        printf("after sort: \n");
        print_array(myarray, n);
        printf("\n");
    }
    else{
        const clock_t begin_time = clock();

        heapsort(myarray, n-1);
        const clock_t end_time = clock();
    
        dur = (float)(end_time - begin_time) /  CLOCKS_PER_SEC;
    }

    printf("%zu, %zu, %zu, %f \n", n, comp, shift, dur);


    free(myarray);
    return EXIT_SUCCESS;
}
