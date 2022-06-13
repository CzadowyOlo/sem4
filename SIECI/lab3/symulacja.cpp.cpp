#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>


using namespace std;

string kabel[20] = {" "};
size_t dl_kabla = 20;
size_t A_time=1;


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
    int signal_lenght = 3;
    

    for (size_t i = position; i < dl_kabla && i < A_time; i++)
    {
        if(i >= signal_lenght)
            kabel[i-signal_lenght] = " ";
        kabel[i] = "A";
    }
    for (size_t i = position; i >= 0 && i < A_time; i--)
    {
     
        kabel[i+signal_lenght] = " ";
        kabel[i] = "A";
    }
    
    


}


int main(void){

    print_kabel();

    for (size_t i = 0; i < 100; i++)
    {
        send_signal('A',0,100);
        A_time++; 
        print_kabel();
        usleep(1000000);
    }
    

    return 0;
}