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

int randomPartition(int tab[], int p, int q){
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
    }

    if (i != p){
            swap(tab[i], tab[p]);
            shifts++;
        }

    return i;
}

int randomSelect(int tab[], int p, int q, int i){
    int r;
    int k;

    if (p == q){
        return tab[p];
    }

    r = randomPartition(tab, p, q);
    k = r - p + 1;

    if (k == i) return tab[r];
    if (i < k){
        return randomSelect(tab, p, r - 1, i);
    }
    else{
        return randomSelect(tab, r + 1, q, i - k);
    }

}

int main(int argc, char *argv[]){

    int i; // = atoi(argv[1]);
    int k = atoi(argv[1]);

    int n;
    cin >> n;
    cin >> i;
    int mytab[n];

    for (int i = 0; i < n; i++){
        cin >> mytab[i];
    }

    // cout<<"Stan początkowy: \n";
    // printer(mytab, n);

    const clock_t begin_time = clock();
    int wynik = randomSelect(mytab, 0, n - 1, k);
    const clock_t end_time = clock();
    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;

    // cout<<"\nszukana statystyka ("<<i<<"-ty min element: "<<wynik<<endl;
    // cout<<"Stan końcowy: \n";
    // printer(mytab, n);
    cout<<endl<<n<<" "<<comparisions<<" "<<shifts<<" "<<dur*1000<<" ";


    return 0;

}
