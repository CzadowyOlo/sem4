#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <tgmath.h>
#include "prior.h"

static size_t shifts = 0;
static size_t compar = 0;
// TODO: 
// f max-heapify
// f build-max-heap
// f 

static inline size_t parent_i (size_t i){ // git
    return (i-1) >> 1;
}

static inline size_t left_i (size_t i){ //git
    return ((i << 1) | 1);
}

static inline size_t right_i (size_t i){ // git
    return (((i+1) << 1));
}

void max_heapify(unsigned array[], size_t i, size_t heapsize){
    size_t l = left_i(i);
    size_t r = right_i(i);
    size_t largest = 0;

    if (l < heapsize && array[l] > array[i]){
        largest = l;
    }
    else{
        largest = i;
    }

    if (r < heapsize && array[r] > array[largest]){
        largest = r;
    }
    if (largest != i){
        swap(array[i], array[largest]);
        max_heapify(array, largest, heapsize);
    }
}


unsigned heap_maximum(unsigned array[]){
    return array[0];
}

unsigned heap_extract_max(unsigned array[], size_t heapsize){
    if(heapsize == __SIZE_MAX__){
        printf("cippppppppppppppppp\n");
        return 213769;
    }
    unsigned max = array[0];
    array[0] = array[heapsize-1];
    max_heapify(array, 0, heapsize - 1);
    return max;
}

void heap_increase_key(unsigned array[], size_t i, unsigned key){
    if (key < array[i]){
        printf("skurwiło sie \n");
        return;
    }
    array[i] = key;
    while ( i > 0 && array[parent_i(i)] < array[i]){
        swap(array[i], array[parent_i(i)]);
        i = parent_i(i);
    }

}

void max_heap_insert(unsigned array[], unsigned key, size_t heapsize){
    array[heapsize] = 0;
    heap_increase_key(array, heapsize, key);
}



void print_array(unsigned tab[], size_t n)
{
    if( n >= 1){

    printf(" {");
    for (size_t i = 0; i < n - 1; i++){
        printf("%d, ", tab[i]);
    }    

    printf("%d }\n", tab[n-1]);
    }
}



// global variables used in `print_HEAP`
static char* left_trace; // needs to be allocaded with size
static char* right_trace; // needs to be allocaded with size

void print_HEAP(unsigned array[], size_t current, int depth, char prefix, size_t n)
{
  if( current >= n ) return;
  if( left_i(current) < n ){
    print_HEAP(array, left_i(current), depth+1, '/', n);
  }
  if(prefix == '/') left_trace[depth-1]='|';
  if(prefix == '\\') right_trace[depth-1]=' ';
  if( depth==0) printf("-");
  if( depth>0) printf(" ");
  for(int i=0; i<depth-1; i++)
    if( left_trace[i]== '|' || right_trace[i]=='|' ) 
    {
      printf("| ");
    } else 
    {
      printf("  ");
    }
  if( depth>0 ) printf("%c-", prefix);
  printf("[%d]\n", array[current]);
  left_trace[depth]=' ';
  if( right_i(current) < n ){
    right_trace[depth]='|';
    print_HEAP(array, right_i(current), depth+1, '\\', n);
  }
}
void fill_traces(size_t n)
{
    left_trace  = (char*)malloc((sizeof(char)*(unsigned long)n) + 1);
    right_trace = (char*)malloc((sizeof(char)*(unsigned long)n) + 1);
    for(size_t i=0; i<=n; i++)
    {
        left_trace[i]=' ';
        right_trace[i]=' ';
    }
}

void print_heap(unsigned array[], size_t n)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HEAP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    print_HEAP(array, 0, 0, '-', n);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~ END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int main(void){

    //assert(left_i(0) == 1);
    size_t n; // size of array
    unsigned k;
    scanf("%zu", &n);
    printf("n = %zu \n", n);

    unsigned myarray[n]; // array to be rebuild as heap and sorted

    if ( n > 50){

        for (size_t i = 0; i < n; i++){
            scanf("%u", &k);
            myarray[i] = k;
            max_heap_insert(myarray, k, i);
        }

        unsigned cippa;
        for(size_t i = n-1; i < __SIZE_MAX__; i--){
            cippa = heap_extract_max(myarray, i+1);
        }
    }
    else{
        fill_traces(n);

        for (size_t i = 0; i < n; i++){
            scanf("%u", &k);
            printf("key: %d \n", k);
            myarray[i] = k;
            max_heap_insert(myarray, k, i);
            print_heap(myarray, i+1);
        }

        printf("\n \n now i will extract \n \n \n");


        for(size_t i = n-1; i < __SIZE_MAX__; i--){
            printf("max elem: %d \n", heap_extract_max(myarray, i+1));
            print_heap(myarray, i);
        }


        free(left_trace);
        free(right_trace);
    }
    

    return EXIT_SUCCESS;
}
