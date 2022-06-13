#include <cmath>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

string generate_crc(string message, const size_t frame_size, const string crc_divider){

    string x = "";
    for (size_t i = 0; i < frame_size; i++)
    {
        x = x + message[i];
    }

    int crc_lenght = crc_divider.length();
    x.append(crc_lenght-1, '0');

    for (size_t i = 0; i < frame_size - 1; i++)
    {
        if (x[i] == '1')
        {
            for (size_t j = 0; j < crc_lenght; j++)
            {
                if (x[i+j] == crc_divider[j])
                    x[i+j] = '0';
                else
                    x[i+j] = '1';            
            }
        }
    }
    return x.substr(frame_size);
}

string encode_message(const char message[], size_t frame_size, const string frame_bound, const string crc_div){
    if (frame_size == 0){
        return "";
    }
    string x = "";
    int danger = 0;
    size_t size = frame_size;
    for(int i = 0; i < frame_size; i++){
        if(message[i] == '1'){
            danger++;
        }
        else{
            danger = 0;
        }
        x = x + message[i];
        if(danger == 5){
            x = x + "0";
            danger = 0;
            size++;
        }
    }
    string crc = generate_crc(x, size, crc_div);
    return frame_bound + x + crc + frame_bound;
}

void print_message(char message[], size_t frame_size){
    
    for (size_t i = 0; i < frame_size; i++){
        cout << message[i];
        cout << endl;
    }
        
}


int main(void){

    ifstream myfile;
    myfile.open("testor.txt");

    ofstream output;
    output.open("w.txt");
    size_t frame_size;
    size_t counter = 0;
    int danger = 0;

    cout << "Podaj wielkosc ramki: ";
    cin >> frame_size; 

    string znacznik = "01111110";
    char message[frame_size];
    string coded_message = "";
    
    cout<<"pipa"<<endl;

    size_t i = 0;

    while ( !myfile.eof())
    {
        
        for (i = 0; i < frame_size; i++){
            myfile >> noskipws >> message[i];
            if(myfile.eof()){
                break;
            }
        }

       
        coded_message = encode_message(message, i, znacznik, "1011");
        cout<< "frame to send: "<<coded_message<<endl;
        output << coded_message;
    }

    myfile.close();
    output.close();

    return 0;
}
