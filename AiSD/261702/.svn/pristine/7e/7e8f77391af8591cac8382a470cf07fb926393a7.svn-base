//InsertionSort
#include <iostream>
#include <stdlib.h> 
#include <chrono>

using namespace std;


long int comparisions = 0;
long int shifts = 0;

void printer (int array[], int n){
    cout<<"{";
    for(int i = 0; i < n; i++){
        printf("%d, ", array[i]);
    }
    cout<<"}\n";
    return;
}

void insertionSort(int array[], int n){
    int i, key;
    
    for(int j = 1; j <n; j++){
        key = array[j];
        i = j-1;
        while(i>=0 && array[i] > key){
            comparisions++;
            array[i+1] = array[i];
            shifts++;
            i--;
        }
        comparisions++;
        array[i+1] = key;
        printer(array, n);
    }
    
}

void insertionSortBig(int array[], int n){
    int i, key;
    
    for(int j = 1; j <n; j++){
        key = array[j];
        i = j-1;
        while(i>=0 && array[i] > key){
            comparisions++;
            array[i+1] = array[i];
            shifts++;
            i--;
        }
        comparisions++;
        array[i+1] = key;
        
    }
    
}

int main(){
    int n;
    cin >> n;
    int mytab[n];

    

    for (int i = 0; i < n; i++){
        cin >> mytab[i];
    }

    if(n <= 50){
        printf("Array of %d-elements before sorting: \n", n);
        printer(mytab, n);
    }
    const clock_t begin_time = clock();
    if(n<=50){
        insertionSort(mytab, n);
    }
    else{
        insertionSortBig(mytab, n);
    }
    
    
    const clock_t end_time = clock();
    
    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;

    if(n <= 50){
        printf("Array of %d-elements after sorting: \n", n);
        printer(mytab, n);
        
    }
    else{
        //printf("size of array: %d\n comparisions: %ld\n       shifts: %ld \ntime(milli_s): %f \n", n, comparisions, shifts, dur*1000);
        cout<<endl<<n<<" "<<comparisions<<" "<<shifts<<" "<<dur*1000<<" ";

    }


}