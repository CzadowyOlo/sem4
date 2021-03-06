//QuickSort

#include <iostream>
#include <stdlib.h> 
#include <chrono>
#include <random>

using namespace std;

long int comparisions = 0;
long int shifts = 0;

void printer (int tab[], int n){
    cout<<"{";
    for(int i = 0; i < n; i++){
        printf("%d, ", tab[i]);
    }
    cout<<"}\n";
    return;
}

int partitionLomuto(int tab[], int p, int q, int n){
    //srand time(NULL);
    int pivot = tab[p];
    int i = p;

    for( int j = p + 1; j <= q; j++){
        comparisions++;
        if (tab[j] <= pivot){
            i++;
            if(tab[i] != tab[j]) swap(tab[i], tab[j]);
            shifts++;
        }
        printer(tab, n);
    }

    if (i != p){
            swap(tab[i], tab[p]);
            shifts++;
            printer(tab, n);
        }

    return i;
}


void quickSort(int tab[], int p, int q, int n){
    if (p < q){
        int r = partitionLomuto(tab, p, q, n);
        quickSort(tab, p, r - 1, n);
        quickSort(tab, r + 1, q, n);
    }
}


int partitionLomutoBig(int tab[], int p, int q, int n){
    //srand time(NULL);
    srand(time(NULL));
    auto g = mt19937{random_device()()};
    auto u = uniform_int_distribution<int> (p,q);
    int randix = u(g);
    int pivot = tab[p];
    int i = p;

    for( int j = p + 1; j <= q; j++){
        comparisions++;
        if (tab[j] <= pivot){
            i++;
            if(tab[i] != tab[j]) swap(tab[i], tab[j]);
            shifts++;
        }
        //printer(tab, n);
    }

    if (i != p){
            swap(tab[i], tab[p]);
            shifts++;
            //printer(tab, n);
        }

    return i;
}




void quickSortBig(int tab[], int p, int q, int n){
    if (p < q){
        int r = partitionLomutoBig(tab, p, q, n);
        quickSortBig(tab, p, r - 1, n);
        quickSortBig(tab, r+ 1, q, n);
    }
}

int main(){
    int n, nulle;
    cin >> n;
    int mytab[n];
    // cin >> nulle;
    

    for (int i = 0; i < n; i++){
        cin >> mytab[i];
    }

    if(n <= 50){
        printf("Array of %d-elements before sorting: \n", n);
        printer(mytab, n);
    }
    const clock_t begin_time = clock();
    
    if(n<=50){
        quickSort(mytab, 0, n-1, n);
    }
    else{
        quickSortBig(mytab, 0, n-1, n);
    }
    
    
    const clock_t end_time = clock();
    
    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;

    if(n <= 50){
        printf("Array of %d-elements after sorting: \n", n);
        printer(mytab, n);
        
    }
    else{
        //printf("size of tab: %d\n comparisions: %ld\n       shifts: %ld \ntime(milli_s): %f \n", n, comparisions, shifts, dur*1000);
        cout<<endl<<n<<" "<<comparisions<<" "<<shifts<<" "<<dur*1000<<" ";

    }
}
