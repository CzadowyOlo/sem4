#include <random>
#include <iostream>
#include <stdlib.h> 

using namespace std;

int main(int argc, char *argv[])
{

    int n = atoi(argv[1]);

    cout<<n<<endl;

    
    int tab[n];
	
    
    unsigned long int sum = 0;
	for(int i = 0; i < n; i++) {
		tab[i] = i;
        cout << tab[i]<<endl;
	}
    

    return 0;
}