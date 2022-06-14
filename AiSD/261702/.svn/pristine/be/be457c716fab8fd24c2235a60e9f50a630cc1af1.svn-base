//HybridSort
#include <iostream>
#include <stdlib.h> 
#include <chrono>

using namespace std;

long int comparisions = 0;
long int shifts = 0;
int part1, part2;

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

void hybridSortBig(int tab[], int left, int right, int change)
{
    while (left < right)
    {
        if (right - left + 1 < change)
        {
            insertionSortBig(tab, right + 1);
            break;
        }

        else

        {
            int pivot = partitionLomutoBig(tab, left, right-1, right);

            if (pivot - left < right - pivot)
            {
                hybridSortBig(tab, left, pivot - 1, change);
                left = pivot + 1;
            }
            else
            {
                hybridSortBig(tab, pivot + 1, right, change);
                right = pivot - 1;
            }
        }
    }
}

void hybridSort(int tab[], int left, int right, int change)
{
    while (left < right)
    {
        if (right - left + 1 < change)
        {
            insertionSort(tab, right + 1);
            return;
        }

        else

        {
            int pivot = partitionLomuto(tab, left, right - 1, right);

            if (pivot - left < right - pivot)
            {
                hybridSort(tab, left, pivot - 1, change);
                left = pivot + 1;
            }
            else
            {
                hybridSort(tab, pivot + 1, right, change);
                right = pivot - 1;
            }
        }
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
        hybridSort(mytab, 0, n-1, 6);
    }
    else{
        hybridSortBig(mytab, 0, n-1, 6);
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