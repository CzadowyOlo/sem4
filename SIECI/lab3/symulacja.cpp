#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

string kabel[10] = {" "};
size_t dl_kabla = 10;

void print_kabel(){

    
    for (size_t i = 0; i < dl_kabla; i++)
    {
        cout << "-----";       
    }
    cout << endl;
    cout << "|";
    for (size_t i = 0; i < dl_kabla; i++)
    {
        cout << kabel[i] << "    |";       
    }
    cout << endl;
    for (size_t i = 0; i < dl_kabla; i++)
    {
        cout << "-----";       
    }
    cout << endl;    
}

void clear_kabel(){
    for (size_t i = 0; i < dl_kabla; i++)
        kabel[i] = " ";
}


void send_signal(char ruter_name, int position, int prob_to_send_mes){
    srand(time(NULL));
    int signal_lenght = rand() % 6 + 2;
    
    for (size_t i = position; i < dl_kabla; i++)
    {
        
    }
    for (size_t i = position; i >= 0 ; i--)
    {
        
    }
    
    


}


int main(void){

    print_kabel();

    for (size_t i = 0; i < 20; i++)
    {
        

        sleep(1);
    }
    
    

    return 0;
}