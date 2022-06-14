//QuickSort

#include <iostream>
#include <stdlib.h> 
#include <chrono>

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

int myCeil(int x, int y){
    return (x%y == 0)? (x/y) : (x/y + 1);
}
int myFloor(int x, int y){
    return (x%y == 0)? (x/y - 1) : (x/y);
}

void insertionSort(int array[], int p, int q){
    int i, key;
    // cout<<"pocz: "<<p<<" konc: "<<q<<endl;
    for(int j = p + 1; j <= q; j++){
        key = array[j];
        i = j-1;
        while(i>=p && array[i] > key){
            comparisions++;
            array[i+1] = array[i];
            shifts++;
            i--;
        }
        comparisions++;
        array[i+1] = key;
        
    }
    
}


int Select(int tab[], int p, int q){
    //assume tab ma 12 elementow
    //we start on whole tab from p = 0 to q = n-1
    int left = p;
    int len = q - p + 1; //count of elements of array
    int maks; //last full five

    int medians_counter = myCeil(len,5);
    int medians[medians_counter];
    int curr_median = 0;

    // int r, k;
    // int x = -1000;

    if(len > 5){
        maks = (len / 5) * 5 -1;
        cout<<"mymaks is: "<<maks<<endl;
    } 
    else{
        cout<<"len was to small"<<endl;
        insertionSort(tab, p, q);
        maks = -1;
        medians[curr_median] = tab[left + myFloor(len, 2)];
        curr_median++;
    }

    // case with 5 elem to sort
    while(left < maks){
        cout<<"done"<<endl;
        insertionSort(tab, left, left + 4);
        //drop medians
        medians[curr_median] = tab[left + 2];
        curr_median++;
        left+=5;
    }
    if(maks > 1 && left > maks){
        if(left == q){
            //nothing to sort, only one element as median - tab[q]
            // drop median
            medians[curr_median] = tab[left];
            curr_median++;
        }
        else if(left < q){
            insertionSort(tab, left, q); //sorting rests
            // drop median
            medians[curr_median] = tab[left + myFloor((q-left + 1),2)];
            curr_median++;
        }
    }
    // cout<<"partly sorted tab: "<<endl;
    // printer(tab, p, q+1);
    // cout<<"tab of medians before sort: "<<endl;
    // printer(medians, 0, curr_median);
    // recursion
    if(medians_counter > 5){
        return Select(medians, 0, curr_median-1);
    }
    else{
        if(curr_median == 1){
            return medians[0];
        }
        else{
            // cout<<"sorting of las tab of medians..."<<endl;
            insertionSort(medians, 0, curr_median-1);
            return medians[myFloor((curr_median - 1), 2)];
            // cout<<"tab of medians after sort:"<<endl;
            // printer(medians, 0, curr_median);
            // cout<<"pivot is: "<<x<<endl;
        }
    }
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