#include <iostream>
#include <fstream>

using namespace std;

bool check_znacznik(string znacznik, char flag[]){

    size_t z_len = znacznik.length();
    streamsize z_f = 8;

    if(z_f != z_len)
        return false;

    for (size_t i = 0; i < z_len; i++)
    {
        if (flag[i] != znacznik[i])
            return false;
    }
    
    return true;
}

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

string char_arr_to_string(char arr[], size_t arr_size){
    
    string str="";
    for (size_t i = 0; i < arr_size; i++)
    {
        str = str + arr[i];
    }
    
    return str;
}

string get_n_bits(ifstream &file, size_t n){

    string str = "";
    char bit;
    if(file.eof())
        return "";
    for (size_t i = 0; i < n; i++)
    {
        file >> noskipws >> bit;
        str = str + bit;
        if(file.eof())
            break;
    }
    return str;
}

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

int main(void){

    ifstream w;
    w.open("w.txt");
    ofstream Z;
    Z.open("Z_decoded.txt");

    string znacznik = "01111110";
    size_t znacznik_len = znacznik.length();
    string crc_divider = "1011";
    //char starting_flag[8];
    string message="";
    string ending_flag;
    string starting_flag;
    size_t mes_len;
    char bit;
    bool starting_flag_ok;
    bool ending_flag_ok;

    starting_flag = get_n_bits(w ,znacznik_len);
    if (znacznik == starting_flag)
        starting_flag_ok = true;
    else
         starting_flag_ok = false;

    cout << "Starting flag pobrane = " << starting_flag << endl;
    
    while(!w.eof()){
        cout<<"ci"<<endl;
        //check_znacznik(znacznik,starting_flag);
        for (size_t i = 0; i < 8; i++)
        {
            if(w.eof())
                break;
            w >> noskipws >> bit;
            message = message + bit;
        }
        cout << "first 8 bits of message = " << message << endl;
        
        if(message == znacznik){
            message=get_n_bits(w,znacznik_len);
        }
        
        mes_len = message.length();
        while(znacznik != message.substr(mes_len-8))
        {
            if(w.eof())
                break;
            w >> noskipws >> bit;
            message = message + bit;
            mes_len++;
        }
        cout << "message = " << message << ", mes_len = " << mes_len <<  endl;
        // w tym momencie doszliśmy do najbliższego poprawnego znacznika
        ending_flag = message.substr(mes_len-8);
        cout << "ending_flag = " << ending_flag << endl;
        // Sprawdzamy czy znacznik końca obecnej ramki i nastepnej są prawidłowe
        message = message.substr(0,mes_len-8);
        cout << "message bez flagi end = " << message << ", mes_len = " << mes_len <<  endl;
        if (check_crc(message, crc_divider))
        {
            cout << "crc git" << endl;
            if (starting_flag_ok)
            {  
                cout << "starting_flag_ok = " << starting_flag_ok << endl;
                cout << "message do pliku= " << message <<  endl;
                Z << decode_message(message, crc_divider);
                
                // pobieramy znacznik_startowy następnej ramki
                starting_flag = get_n_bits(w ,znacznik_len);
                if (znacznik == starting_flag)
                    starting_flag_ok = true;
                else
                    starting_flag_ok = false;
            }
            else{
                // flaga startowa ramki zepsuta
                cout << "flaga startowa ramki zepsuta = " << starting_flag << endl;
                 // pobieramy znacznik_startowy następnej ramki
                starting_flag = get_n_bits(w ,znacznik_len);
                if (znacznik == starting_flag)
                    starting_flag_ok = true;
                else
                    starting_flag_ok = false;
            }
        }
        else
        {
            
            cout << "CRC nie przeszło = nie wysyłam ramki" << endl;
            starting_flag = ending_flag;
            starting_flag_ok = true;
            cout << "flaga do której wczesniej doszliśmy jest poczatkowym znacznikiem kolejnej ramki"<<endl;
        }
        message = "";
    }

    Z.close();
    w.close();
    


    return 0;
}