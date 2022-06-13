#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include <algorithm>

using namespace std;

int modulo(int x, int y){
    int z = x%y;
    if (z >= 0){
        return z;
    }
    else{
        return y + z;
    }
}

bool check_crc(string message, const size_t frame_size, const string crc_divider){

    if(frame_size < 4) return false;

    string x = "";
    for (size_t i = 0; i < frame_size; i++)
    {
        x = x + message[i];
    }
    cout<<x<<endl;
    int crc_lenght = crc_divider.length();
    //x.append(crc_lenght-1, '0');

    for (size_t i = 0; i < frame_size - crc_lenght + 1; i++)
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
    cout<<x<<endl;
    if(x.substr(x.length()-3) == "000"){
        return true;
    }
    else{
        return false;
    }

}

int main(){

    // int x = 6;
    // int y = 9;

    // cout<<min(x,y)<<" "<<max(x,y)<<endl;
    // cout<<((x - y)%8)<<endl;
    // cout<<((y-x)%8)<<endl;

    // cout<<modulo(x-y, 8)<<endl;
    // cout<<modulo(y-x, 8)<<endl;

    // string dupa = "seks_w_dupsko";
    // int len = dupa.length();
    // string bez_osm = dupa.substr(0, len - 8);
    // string osm = dupa.substr(len - 8, len);

    // cout<<dupa<<endl<<bez_osm<<endl<<osm<<endl;

    // 10011010111110010
    // string div = "1011";
    // string test = "10011010111110010";
    // string after = "";

    // cout<<"test: "<<test<<endl; 
    // cout<<"test len:  "<<test.length()<<endl;
    // //after = generate_crc(test, test.length(), div);
    // //cout<<"test: "<<after<<endl;
    // //cout<<"after len: "<<after.length()<<endl;
    // //cout<<"new crc: "<<after.substr(after.length()-3)<<endl;
    // if(check_crc(test, test.length(), div)){
    //     cout<<"git"<<endl;
    // }
    // else{
    //     cout<<"chuj"<<endl;
    // }
    for (int i = 0; i < -1; i++){
        cout<<"cipa"<<endl;
    }

    return 0;
}