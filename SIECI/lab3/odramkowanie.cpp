#include <cmath>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

string decode_message(string message, const string crc_divider){

    
    size_t mes_len = message.length()-(crc_divider.length()-1);

    int counter_1 = 0;
    string dec_mes = ""; 

    for (size_t i = 0; i < mes_len; i++)
    {
        dec_mes = dec_mes + message[i];
        
        if (message[i] == '0')
            counter_1 = 0;
        else
            counter_1++;

        if (counter_1 == 5){
            i++;
            counter_1 = 0;
        }  
    }

    return dec_mes;
}

// bool check_crc(string message, const size_t frame_size, const string crc_divider){

//     if(frame_size < 4) return false;

//     string x = "";
//     for (size_t i = 0; i < frame_size; i++)
//     {
//         x = x + message[i];
//     }
//     cout<<x<<endl;
//     int crc_lenght = crc_divider.length();
//     //x.append(crc_lenght-1, '0');

//     for (size_t i = 0; i < frame_size - crc_lenght + 1; i++)
//     {
//         if (x[i] == '1')
//         {
//             for (size_t j = 0; j < crc_lenght; j++)
//             {
//                 if (x[i+j] == crc_divider[j])
//                     x[i+j] = '0';
//                 else
//                     x[i+j] = '1';            
//             }
//         }
//     }
//     cout<<x<<endl;
//     if(x.substr(x.length()-3) == "000"){
//         return true;
//     }
//     else{
//         return false;
//     }

// }

bool check_crc(string message, string crc_divider){
    //crc divider = 1011
    //message ma postać 1001101101|101
    //mes_len = 13
    //crc_len = 4
    //crc divider = "1011"
    

    size_t crc_len = crc_divider.length();
    size_t mes_len = message.length();
    if (mes_len < crc_len){
        cout << "Frame NOT correct" << endl;
        return false;
    }

    cout << message << " = x" << endl;
    for (size_t i = 0; i < mes_len - (crc_len - 1) - 1; i++)
    {
        for (size_t k = 0; k < i; k++)
        {
            cout << " ";
        }
        cout << crc_divider << endl;
        if (message[i] == '1')
        {
            for (size_t j = 0; j < crc_len; j++)
            {
                if (message[i+j] == crc_divider[j])
                    message[i+j] = '0';
                else
                    message[i+j] = '1';            
            }
            cout << message << " = x in for" << endl;
        }
    }
    cout << "ending x = " << message << endl;
    string correct = "";
    correct.append(crc_len-1, '0');
    if (message.substr(mes_len-(crc_len-1)) == correct)
    {
        cout << "Frame correct" << endl;
        return true; 
    }
    else{
        cout << "Frame NOT correct" << endl;
        return false;
    }
}

bool check_marker(const string marker, const string my_marker){

    for (int i = 0; i < 8; i++){
        if(marker[i] != my_marker[i]) return false;
    }

    return true;
}

string get_marker(string marker, ifstream *w){

    size_t marker_len = marker.length();
    char bit;
    string my_marker = "";

    for(size_t i = 0; i < marker_len; i++){
        cout<<"i: "<<i<<endl;
        *w >> noskipws >> bit;
        my_marker += bit;
    }
    cout<<"my_marker: "<<my_marker<<endl;
    return my_marker;
}

void wait_for_last_marker(string *marker, string *message, string *my_marker, int *mess_length, ifstream *w){
    char bit;
    int len = 8;
    string pom = *my_marker;
    while(*marker != pom && ! (*w).eof() ){
            
            //cout<<"marker: "<<*marker<<endl;
            //cout<<"my_marker: "<<*my_marker<<endl;

            *w >> noskipws >> bit;
            *message = *message + bit;
            pom = pom + bit;
            len++;
            
            cout<<"pom1: "<<pom<<endl;
            pom.erase(0,1);
            cout<<"pom2: "<<pom<<endl;


            //cout<<"my_marker2: "<<*my_marker<<endl;
            //(*my_marker).erase(0,1);
            //cout<<"my_marker3: "<<*my_marker<<endl;
            *mess_length++;
            //cout<<"cipa"<<endl;
            
            
        }
        *my_marker = pom;
        cout<<"did got end marker"<<endl;
}


void get_8(string *message, int *mess_length, string *my_marker, int *my_marker_length, ifstream *w){

    char bit;
    for (size_t i = 0; i < 8; i++){
            *w >> noskipws >> bit;
            *my_marker += bit;
            *message += bit;
        }
        *mess_length = 8;
        *my_marker_length = 8;

}


int main(void){

    ifstream w;
    w.open("w.txt");
    ofstream z;
    z.open("dekoded.txt");

    string marker = "01111110";
    string my_start_marker = "";
    string my_end_marker = "";
    string crc_div = "1011";

    string message = "";

    // char znacznik_geted[8];
    int mess_length = 0;
    int my_marker_length = 0;
    char bit;
    bool if_first = false;
    bool if_last = false;
    bool broken_last = false;
    bool do_getnext8 = true;
    int fram_count = 0;
    string zepsute = "";

    cout<<"chuj"<<endl;

    while(! w.eof()){
        if(!if_first){
            //brokens++;
            my_start_marker = get_marker(marker, &w); // 1st step: get first marker.len bits and check if it is marker
            cout<<"first marker: "<<my_start_marker<<endl;
            if_first = check_marker(marker, my_start_marker);
            cout<<if_first<<endl;
            while(!if_first){
                cout<<"dupa"<<endl;
                mess_length = 8;
                wait_for_last_marker(&marker, &my_start_marker, &my_start_marker, &mess_length, &w); // wczytalem las marker z 1st ramki //lub start marker z 2nd ramki
                message = "";
                cout<<"origin marker: "<<marker<<endl;
                cout<<"messagecip: "<<message<<endl;
                message = get_marker(marker, &w);
                cout<<"messageCIPA: "<<message<<endl;
                mess_length = 8;
                if(check_marker(marker, message)){ // got last marker z 1st ramki
                    message = "";
                    my_end_marker = "";
                    mess_length = 0;
                    my_marker_length = 0;
                    if_first = true;
                    fram_count++;
                } // now i have red start marker z 2nd ramki
                else{ //wczytalem juz first marker z drugiej ramki i jeszcze za dużo
                    if_first = true;
                    // do not get8 i next step
                    my_end_marker = message;
                    do_getnext8 = false;
                }
            }
        }
        if(if_first){ // i did get starting marker
            if(do_getnext8){
                get_8(&message, &mess_length, &my_end_marker, &my_marker_length, &w);
            }
            do_getnext8 = true;
            wait_for_last_marker(&marker, &message, &my_end_marker, &mess_length, &w);
            cout<<"my mess0: "<<message<<endl;
            mess_length = message.length();
            cout<<"mess len: "<<mess_length<<endl;
            message = message.substr(0, mess_length - 8);
            mess_length = message.length();
            cout<<"my mess: "<<message<<endl;
            // znalazłem las marker z 1st frame albo first marker z 2nd frame
            if(check_crc(message, crc_div)){ //znalazłem last marker z 1st ramki
                if_last = true;
                if_first = false;
                //send
                cout<<"my mess: "<<message;
                z << decode_message(message, crc_div);
                fram_count++;
                message = "";
                mess_length = 0;
                my_end_marker = "";
                zepsute = zepsute + ", " +  to_string(fram_count);
            }
            else{ //znalazłem first marker z 2nd ramki ||| albo crc noie przeszło z innego powodu-wcale nie znalazłem drugiego
                //crc bad, a ja nadmiarowo wziolem piersza, czyli bede mial jeszcze jedno pierwszo
                fram_count++;
                if_last = false;
                my_start_marker = my_end_marker;
                my_end_marker = "";
                if_first = true;
                message = "";
                mess_length = 0;
                message = get_marker(marker, &w);
                if(check_marker(marker, message)){
                    message = "";
                    mess_length = 0;
                    //fram_count++;
                }
                //brokens++;
            }

        }
    }

    cout<<"dobre: "<<zepsute<<endl;

}
