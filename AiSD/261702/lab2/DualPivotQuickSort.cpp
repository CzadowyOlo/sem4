//DualPivotQuickSort

//QuickSort

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

void partition(int A[], int left, int right, int n)
{
    int x = A[left];  // pivot 1
    int y = A[right]; // pivot 2

    int i = left + 1;
    int k = right - 1;
    int j = i;
    int d = 0;

    if (x > y)
    {
        shifts++;
        comparisions++;
        swap(A[left], A[right]);
        x = A[left];
        y = A[right];
    }
    printer(A, n);
    cout << "pivot1: " << x << " | pivot2: " << y << endl;

    while (j <= k)
    {
        if (d >= 0)
        {
            comparisions++;
            if (A[j] < x)
            {
                shifts++;
                swap(A[i], A[j]);
                i++;
                j++;
                d++;
                printer(A, n);
            }
            else
            {
                comparisions++;
                if (A[j] < y)
                {
                    j++;
                }
                else
                {
                    shifts++;
                    swap(A[j], A[k]);
                    k--;
                    d--;
                    printer(A, n);
                }
            }
        }
        else
        {
            comparisions++;
            if (A[k] > y)
            {
                k--;
                d--;
            }
            else
            {
                comparisions++;
                if (A[k] < x)
                {
                    shifts = shifts + 3;
                    int tmp = A[k];
                    A[k] = A[j];
                    A[j] = A[i];
                    A[i] = tmp;
                    i++;
                    d++;
                    printer(A, n);
                }
                else
                {
                    shifts++;
                    swap(A[j], A[k]);
                    printer(A, n);
                }
                j++;
            }
        }
    }

    shifts = shifts + 2;
    swap(A[left], A[i - 1]);
    swap(A[right], A[k + 1]);
    part1 = i - 1;
    part2 = k + 1;
    printer(A, n);
}

void partitionBig(int A[], int left, int right)
{
    int x = A[left];  // pivot 1
    int y = A[right]; // pivot 2

    int i = left + 1;
    int k = right - 1;
    int j = i;
    int d = 0;

    if (x > y)
    {
        shifts++;
        comparisions++;
        swap(A[left], A[right]);
        x = A[left];
        y = A[right];
    }

    while (j <= k)
    {
        if (d >= 0)
        {
            comparisions++;
            if (A[j] < x)
            {
                shifts++;
                swap(A[i], A[j]);
                i++;
                j++;
                d++;
            }
            else
            {
                comparisions++;
                if (A[j] < y)
                {
                    j++;
                }
                else
                {
                    shifts++;
                    swap(A[j], A[k]);
                    k--;
                    d--;
                }
            }
        }
        else
        {
            comparisions++;
            if (A[k] > y)
            {
                k--;
                d--;
            }
            else
            {
                comparisions++;
                if (A[k] < x)
                {
                    shifts = shifts + 3;
                    int tmp = A[k];
                    A[k] = A[j];
                    A[j] = A[i];
                    A[i] = tmp;
                    i++;
                    d++;
                }
                else
                {
                    shifts++;
                    swap(A[j], A[k]);
                }
                j++;
            }
        }
    }

    shifts = shifts + 2;
    swap(A[left], A[i - 1]);
    swap(A[right], A[k + 1]);
    part1 = i - 1;
    part2 = k + 1;
}

void dualPivotQuickSort(int arr[], int start, int end, int n)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    partition(arr, start, end, n);

    // Sorting the left part
    dualPivotQuickSort(arr, start, part1 - 1, n);

    // Sorting the middle part
    dualPivotQuickSort(arr, part1 + 1, part2 - 1, n);

    // Sorting the right part
    dualPivotQuickSort(arr, part2 + 1, end, n);
}

void dualPivotQuickSortBig(int arr[], int start, int end)
{
    // base case
    if (start >= end)
        return;

    // partitioning the array
    partitionBig(arr, start, end);

    // Sorting the left part
    dualPivotQuickSortBig(arr, start, part1 - 1);

    // Sorting the middle part
    dualPivotQuickSortBig(arr, part1 + 1, part2 - 1);

    // Sorting the right part
    dualPivotQuickSortBig(arr, part2 + 1, end);
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
        dualPivotQuickSort(mytab, 0, n-1, n);
    }
    else{
        dualPivotQuickSortBig(mytab, 0, n-1);
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