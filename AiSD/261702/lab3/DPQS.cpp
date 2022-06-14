#include<iostream>

int comparisions = 0;
int shifts  = 0;

void printer (int tab[], int n){
    std::cout<<"{";
    for(int i = 0; i < n; i++){
        printf("%d, ", tab[i]);
    }
    std::cout<<"}\n";
    return;
}

int partition(int* arr, int low, int high, int* lp);


void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
    shifts  += 3; // swap to zawsze trzy są dla mnie
}
 
void DualPivotQuickSort(int* arr, int low, int high)
{
    comparisions++;
    if (low < high) {
        // lp means left pivot, and rp means right pivot.
        int lp, rp;
        rp = partition(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1);
        DualPivotQuickSort(arr, lp + 1, rp - 1);
        DualPivotQuickSort(arr, rp + 1, high);
    }
}
 
int partition(int* arr, int low, int high, int* lp)
{
    comparisions++;
    if (arr[low] > arr[high]){
         // jest porownanko
        swap(&arr[low], &arr[high]);
    }
    // p is the left pivot, and q is the right pivot.
    int j = low + 1;
    int g = high - 1, k = low + 1, p = arr[low], q = arr[high];
    while (k <= g) {
        comparisions++; // jest porownanko
        // if elements are less than the left pivot
        comparisions++;
        if (arr[k] < p) {
            swap(&arr[k], &arr[j]);
            j++;
        }
 
        // if elements are greater than or equal
        // to the right pivot
        else if (arr[k] >= q) {
            comparisions+=3; // jest porownanko
            while (arr[g] > q && k < g){
                comparisions+=2; // jest porownanko
                g--;
            }
            swap(&arr[k], &arr[g]);
            g--;
            if (arr[k] < p) {
                comparisions++; // jest porownanko
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

void sort(int* nums, int n){
    DualPivotQuickSort(nums, 0, n-1);
}

int main(){
    int n, nulle;
    std::cin >> n;
    std::cin >> nulle;
    int nums[n];

    for(int i = 0; i < n; i++){
        std::cin >> nums[i];
    }
    if(n < 50){
        std::cout << "Before sorting:" << std::endl;
        printer(nums,n);
        std::cout << "During sorting:" << std::endl;
    }
    const clock_t begin_time = clock();
    sort(nums, n);
    const clock_t end_time = clock();
    
    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;
    if (n < 50){
        std::cout << "After sorting:" << std::endl;
        printer(nums, n);
    }
    //check_if_list_sorted(nums, n);
    std::cout << n << " " << comparisions  << " "<<dur*1000 << std::endl;
}