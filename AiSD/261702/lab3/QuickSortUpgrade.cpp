//QuickSort

#include <iostream>
#include <stdlib.h> 
// #include <chrono>
#include<climits>

using namespace std;

long int comparisions = 0;
long int shifts = 0;

int partition(int arr[], int l, int r, int x);
int partitionBig(int arr[], int l, int r, int x);


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
            shifts++;
			comparisions++;
			arr[j + 1] = arr[j];
            j = j - 1;
        }
		shifts++;
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
int Select(int arr[], int l, int r, int k)
{
	// If k is smaller than number of elements in array
	if (k > 0 && k <= r - l + 1)
	{
		int n = r-l+1; // Number of elements in arr[l..r]

		// Divide arr[] in groups of size 5, calculate median
		// of every group and store it in median[] array.
		int i, median[(n+4)/5]; // There will be floor((n+4)/5) groups;
		for (i=0; i<n/5; i++)
			median[i] = findMedian(arr+l+i*5, 5);
		if (i*5 < n) //For last group with less than 5 elements
		{
			median[i] = findMedian(arr+l+i*5, n%5);
			i++;
		}

		// Find median of all medians using recursive call.
		// If median[] has only one element, then no need
		// of recursive call
		int medOfMed = (i == 1)? median[i-1]:
								Select(median, 0, i-1, i/2);

		// Partition the array around a random element and
		// get position of pivot element in sorted array
		int pos = partition(arr, l, r, medOfMed);

		// If position is same as k
		comparisions++;
		if (pos-l == k-1)
			return arr[pos];
		
		comparisions++;
		if (pos-l > k-1) // If position is more, recur for left
			return Select(arr, l, pos-1, k);

		// Else recur for right subarray
		return Select(arr, pos+1, r, k-pos+l-1);
	}

	// If k is more than number of elements in array
	return INT_MAX;
}

int partition(int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i=l; i<r; i++){
		comparisions++;
		if (arr[i] == x)
		break;
	}
	shifts++;
	swap(arr[i], arr[r]);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		comparisions++;
		if (arr[j] <= x)
		{
			shifts++;
			swap(arr[i], arr[j]);
			i++;
		}
	}
	comparisions++;
	swap(arr[i], arr[r]);
	return i;
}

int partitionBig(int arr[], int l, int r, int x)
{
	// Search for x in arr[l..r] and move it to end
	int i;
	for (i=l; i<r; i++){
		comparisions++;
		if (arr[i] == x)
		break;
	}
	shifts++;
	swap(arr[i], arr[r]);

	// Standard partition algorithm
	i = l;
	for (int j = l; j <= r - 1; j++)
	{
		comparisions++;
		if (arr[j] <= x)
		{
			shifts++;
			swap(arr[i], arr[j]);
			i++;
		}
	}
	comparisions++;
	swap(arr[i], arr[r]);
	return i;
}


void quickSort(int tab[], int p, int q, int n){
    if (p < q){
        int pivot = Select(tab, p, q, myFloor(q - p + 1, 2));
        int r = partition(tab, p, q, pivot);
        quickSort(tab, p, r - 1, n);
        quickSort(tab, r + 1, q, n);
    }
}


void quickSortBig(int tab[], int p, int q, int n){
    if (p < q){
        int pivot = Select(tab, p, q, myFloor(q - p + 1, 2));
        int r = partitionBig(tab, p, q, pivot);
        quickSortBig(tab, p, r - 1, n);
        quickSortBig(tab, r+ 1, q, n);
    }
}

int main(){
    
    int n, nulle;
    cin >> n;
    // cin >> nulle;
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
