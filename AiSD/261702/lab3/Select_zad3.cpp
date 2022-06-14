// C++ implementation of worst case linear time algorithm
// to find k'th smallest element
#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

long int porownania = 0;
long int przestawienia = 0;

void wypisz_tablice(int tab[], int n, int subarray_size)
{
    cout << " {";
    for (int i = 0; i < n - 1; ++i)
    {
        cout << tab[i] << ", ";
		if((i+1)%subarray_size == 0) cout<<"|";
    }
    cout << tab[n - 1] << "}" << endl;
}

int partition(int arr[], int l, int r, int k);

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            przestawienia++;
			porownania++;
			arr[j + 1] = arr[j];
            j = j - 1;
        }
		przestawienia++;
        arr[j + 1] = key;
    }
}

// A simple function to find median of arr[]. This is called
// only for an array of size 5 in this program.
int findMedian(int arr[], int n)
{
	//sort(arr, arr+n); // Sort the array
	insertionSort(arr, n);
	return arr[n/2]; // Return middle element
}


// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
int SelectDiffSubarrays(int arr[], int l, int r, int k, int subarray_size)
{
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		int n = r-l+1; // Number of elements in arr[l..r]

		// Divide arr[] in groups of size 5, calculate median
		// of every group and store it in median[] array.
		int i, median[(n+(subarray_size-1))/subarray_size]; // There will be floor((n+4)/5) groups;
		for (i=0; i<n/subarray_size; i++){
			median[i] = findMedian(arr+l+i*subarray_size, subarray_size);
            // wypisz_tablice(arr,n,subarray_size);
        }
		if (i*subarray_size < n) //For last group with less than 5 elements
		{
			median[i] = findMedian(arr+l+i*subarray_size, n%subarray_size);
			i++;
            // wypisz_tablice(arr,n,subarray_size);
		}

		// Find median of all medians using recursive call.
		// If median[] has only one element, then no need
		// of recursive call
		int medOfMed = (i == 1)? median[i-1]:
								SelectDiffSubarrays(median, 0, i-1, i/2, subarray_size);

		// Partition the array around a random element and
		// get position of pivot element in sorted array
		int pos = partition(arr, l, r, medOfMed);

		// If position is same as k
		porownania++;
		if (pos-l == k-1)
			return arr[pos];
		
		porownania++;
		if (pos-l > k-1) // If position is more, recur for left
			return SelectDiffSubarrays(arr, l, pos-1, k, subarray_size);

		// Else recur for right subarray
		return SelectDiffSubarrays(arr, pos+1, r, k-pos+l-1, subarray_size);
	}

	// If k is more than number of elements in array
	return INT_MAX;
}

// It searches for x in arr[l..r], and partitions the array
// around x.
int partition(int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i=l; i<r; i++){
		porownania++;
		if (arr[i] == x)
		break;
	}
	przestawienia++;
	swap(arr[i], arr[r]);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		porownania++;
		if (arr[j] <= x)
		{
			przestawienia++;
			swap(arr[i], arr[j]);
			i++;
		}
	}
	przestawienia++;
	swap(arr[i], arr[r]);
	return i;
}

void merge_over50(int tab[], int l, int m, int r)
{

    int i = l;
    int j = m + 1;
    int k = l;

    int tempTab[r];

    while (i <= m && j <= r)
    {
        if (tab[i] <= tab[j])
        {
            tempTab[k] = tab[i];
            i++;
            k++;
        }
        else
        {
            tempTab[k] = tab[j];
            j++;
            k++;
        }
    }

    while (i <= m)
    {
        tempTab[k] = tab[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        tempTab[k] = tab[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; ++p)
    {
        tab[p] = tempTab[p];
    }
}

void mergeSort_over50(int tab[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergeSort_over50(tab, l, m);
        mergeSort_over50(tab, m + 1, r);
        merge_over50(tab, l, m, r);
    }
}

// Driver program to test above methods
int main(int argc, char *argv[])
{
	int n;  // wielkosc tablicy 
    int x;  // kolejne elementy tablicy
    int k, i;
    cin >> n;
    int tab[n];

    cin >> i; // k-th smallest element, we get this from generator

    k = atoi(argv[1]); //
    int subarray_size = atoi(argv[2]);

    for (int p = 0; p < n; p++)
    {
        cin >> x;
        tab[p] = x;
    }
    if(n<=50){
        cout<< "Tablica wejsciowa: " << endl;
        wypisz_tablice(tab, n,subarray_size);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        int odp = SelectDiffSubarrays(tab, 0, n-1, k, subarray_size);
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        cout << k << " najmniejszy element tablicy to: " << odp << endl;
        cout << "Tablica po wykonaniu selecta: " << endl;
        wypisz_tablice(tab, n, subarray_size);
        cout << "Tablica po przesortowaniu: " << endl;
        mergeSort_over50(tab,0,n-1);
        wypisz_tablice(tab, n, subarray_size);
        cout << "Licznik przestawien: " << przestawienia << endl;
        cout << "Licznik porownan: " << porownania << endl;
    }
    else{
        const clock_t begin_time = clock(); // time
        int odp = SelectDiffSubarrays(tab, 0, n-1, k, subarray_size);
        const clock_t end_time = clock(); // time
        float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;

        cout << n << " "<<porownania<<" "<<przestawienia<<" "<<dur*1000;
       
        
    }
	return 0;
}
