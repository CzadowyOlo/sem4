#include <random>
#include <iostream>
#include <stdlib.h> 

using namespace std;

int main(int argc, char *argv[])
{

    int n = atoi(argv[1]);

    cout<<n<<endl;

    int range = 2*n -1;
    int tab[n];
	// seed
	//random_device rd;
	//seed_seq sd{rd(), rd(), rd(), rd(), rd(), rd(), rd()}; // 4 tab[]s are enough. 8 max.
	auto g = mt19937{random_device()()}; // advanced seeding

    // distribution
	auto u = uniform_int_distribution<int> (0,range);
    
    //-------------------------------------------------------------------
	auto q = uniform_int_distribution<int> (1,n); // getting k-th element 

	// use
    int k = q(g);
    cout<<k<<endl;
    //--------------------------------------------------------------------

    unsigned long int sum = 0;
	for(int i = 0; i < n; i++) {
		tab[i] = u(g);
        //printf("%d th tab[] is: %d \n", i, tab[]);
        sum = sum + tab[i];
        cout << tab[i]<<endl;
	}
    long double ex = (sum * 1.0)/n;
    printf("Ex of %d numbers is: %2.25Lf \n", n, ex);

    //int *addres = &tab;

    return 0;
}


