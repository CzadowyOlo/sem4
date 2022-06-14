//MergeSort
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

void merge(int tab[], int l, int m, int r, int n)
{

    int i = l;
    int j = m + 1;
    int k = l;

    int tempTab[r];

    while (i <= m && j <= r)
    {
        comparisions++;
        if (tab[i] <= tab[j])
        {
            tempTab[k] = tab[i];
            i++;
            k++;
        }
        else
        {
            shifts++;
            tempTab[k] = tab[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        shifts++;
        tempTab[k] = tab[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        shifts++;
        tempTab[k] = tab[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; ++p)
    {
        tab[p] = tempTab[p];
    }
    printer(tab, n);
}

void mergeSort(int tab[], int l, int r, int n)
{

    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort(tab, l, m, n);
        mergeSort(tab, m + 1, r, n);
        merge(tab, l, m, r, n);
    }
}

void mergeBig(int tab[], int l, int m, int r, int n)
{

    int i = l;
    int j = m + 1;
    int k = l;

    int tempTab[r];

    while (i <= m && j <= r)
    {
        comparisions++;
        if (tab[i] <= tab[j])
        {
            tempTab[k] = tab[i];
            i++;
            k++;
        }
        else
        {
            shifts++;
            tempTab[k] = tab[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        shifts++;
        tempTab[k] = tab[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        shifts++;
        tempTab[k] = tab[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; ++p)
    {
        tab[p] = tempTab[p];
    }
}

void mergeSortBig(int tab[], int l, int r, int n)
{

    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSortBig(tab, l, m, n);
        mergeSortBig(tab, m + 1, r, n);
        mergeBig(tab, l, m, r, n);
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
        mergeSort(mytab, 0, n-1, n);
    }
    else{
        mergeSortBig(mytab, 0, n-1, n);
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
