#include<iostream>

int comparisions = 0;
int shifts = 0;

int partition(int* arr, int low, int high, int* lp);
int select_Select(int* tab, int left, int right, int k, int size, int divide_size);
void select_swap(int* tab, int index1, int index2);
int select_partition(int* list, int left, int right, int pivotIndex, int n);
int select_partition_small(int* tab, int left, int right);

void printer (int tab[], int n){
    std::cout<<"{";
    for(int i = 0; i < n; i++){
        printf("%d, ", tab[i]);
    }
    std::cout<<"}\n";
    return;
}

void select_swap(int* tab, int index1, int index2){
    int temp = tab[index1];
    tab[index1] = tab[index2];
    tab[index2] = temp;
    shifts += 3; // 
}

int select_partition(int* list, int left, int right, int pivotIndex, int n){
    int pivotValue = list[pivotIndex];
    select_swap(list, pivotIndex, right); // move pivot to an end
    int storeIndex = left;
    // move all elements smaller than the pivot to the left of the pivot;
    for (int i = left; i <= right-1; i++){
        comparisions+=2;
        if (list[i] < pivotValue){
            select_swap(list, storeIndex, i);
            storeIndex++;
        }
    }
    // Move all elements equal to the pivot right after the smaller elements
    int storeIndexEq = storeIndex;
    for (int i = storeIndex; i <= right-1; i++){
        comparisions+=2;
        if(list[i] == pivotValue){
            select_swap(list, storeIndexEq, i);
            storeIndexEq++;
        }
    }
    select_swap(list, right, storeIndexEq); // Move pivot to its final place
    // Return location ofpivot considering the desired locaiton n
    comparisions++;
    if (n < storeIndex) return storeIndex;
    comparisions++;
    if (n <= storeIndexEq) return n;
    return storeIndexEq;  
}

int select_partition_small(int* tab, int left, int right){
    int i = left+1;
    comparisions++;
    while (i <= right){
        int j = i;
        comparisions+=2;
        while ( j > left && tab[j-1] > tab[j]){
            select_swap(tab, j-1, j);
            j--;
            comparisions+=2;
        }
        i++;
        comparisions++;
    }
    return (left+right)/2;
}

int select_pivot(int* tab, int left, int right, int size, int divide_size){
    // for 5 or less elements just get median
    comparisions++;
    if (right - left < divide_size) return select_partition_small(tab, left, right);
    // otherwise move the medians of five-element subgroups to the first n/5 positions
    for ( int i = left; i <= right; i+= divide_size){
        comparisions++;
        // get the median of the i'th five element subgroup
        int subRight = i+divide_size-1;
        comparisions++;
        if (subRight > right) subRight = right;

        int median5 = select_partition_small(tab, i, subRight);
        select_swap(tab, median5, left + (i-left) / divide_size);
    }
    int mid = (right - left) / (divide_size*2) + left + 1;
    return select_Select(tab, left, left + (right-left)/divide_size, mid, size, divide_size);
}

int select_Select(int* tab, int left, int right, int k, int size, int divide_size){
    comparisions++;
    while (1){
        comparisions++;
        if (left == right) return left;

        int pivot_index = select_pivot(tab, left, right, size, divide_size);
        pivot_index = select_partition(tab, left, right, pivot_index, k);
        if (size < 50){
            printer(tab, size);
        }

        comparisions++;
        if (k==pivot_index){
            return k; 
        } else if (k < pivot_index){
            comparisions++;
            right = pivot_index - 1;
        } else {
            comparisions++;
            left = pivot_index + 1;
        }
    }
}

int select_select(int* tab, int n, int k, int size, int divide_size){
    return select_Select(tab, 0, n-1, k-1, size, divide_size);
}

void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
    shifts += 3; // swap to zawsze trzy są dla mnie
}
 
void DualPivotQuickSort(int* arr, int low, int high, int n)
{
    if (low < high) {
        comparisions++; 
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1,n);
        DualPivotQuickSort(arr, lp + 1, rp - 1,n);
        DualPivotQuickSort(arr, rp + 1, high,n);
        if (n < 50){
            printer(arr, n);
        }
    }
}
 
int partition(int* arr, int low, int high, int* lp)
{
    // p is the left pivot, and q is the right pivot.
    int pivot_index1 = select_pivot(arr, low, high, 100, 5);
    swap(&arr[low], &arr[pivot_index1]);
    int pivot_index2 = select_pivot(arr, low+1, high, 100, 5);
    swap(&arr[high], &arr[pivot_index2]);

    if (arr[low] > arr[high]){
        comparisions++; // jest porownanko
        swap(&arr[low], &arr[high]);
    }
    
    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    while (k <= g) {
        comparisions++;
        // if elements are less than the left pivot
        if (arr[k] < p) {
            comparisions++;
            swap(&arr[k], &arr[j]);
            j++;
        }
 
        // if elements are greater than or equal
        // to the right pivot
        else if (arr[k] >= q) {
            comparisions++; 
            while (arr[g] > q && k < g){
                comparisions++; 
                g--;
            }
            swap(&arr[k], &arr[g]);
            g--;
            if (arr[k] < p) {
                comparisions++; 
                swap(&arr[k], &arr[j]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;
 
    // bring pivots to their appropriate positions.
    swap(&arr[low], &arr[j]);
    swap(&arr[high], &arr[g]);
 
    // returning the indices of the pivots.
    *lp = j; // because we cannot return two elements
    // from a function.
 
    return g;
}

void sort(int* tab, int n){
    DualPivotQuickSort(tab, 0, n-1, n);
}

int main(){
    int n, nulle;
    std::cin >> n;
    std::cin >>nulle;
    int tab[n];

    for(int i = 0; i < n; i++){
        std::cin >> tab[i];
    }
    if(n < 50){
        std::cout << "Before sorting:" << std::endl;
        printer(tab, n);
        std::cout << "During sorting:" << std::endl;
    }
    const clock_t begin_time = clock();
    sort(tab, n);
    const clock_t end_time = clock();
    
    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;
    if (n < 50){
        std::cout << "After sorting:" << std::endl;
        printer(tab, n);
    }
    
    std::cout << n << " " << comparisions  << " "<<dur*1000<< std::endl;
}
