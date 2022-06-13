#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> dictionary; // structure to keep dictionary


// adding basic codes (ASCII) to dictionary (0-255)
void basic_codes_to_dictionary(){
    for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		dictionary[ch] = i;
	}
}

// convert binary rep of number to int value
int binary_to_decimal(string binary)
{
    int decimal = 0;
    for (size_t i = 0; i < binary.length(); i++)
    {
        if (binary[i] == '1')
        {
            decimal = decimal + pow(2, (binary.length() - i - 1));
        }
    }
    return decimal;
}
// and vive versa
string decimal_to_binary(int decimal)
{
    string binary = "";

    if(decimal == 0)
        return "0";

    while (decimal > 0)
    {
        binary = to_string(decimal % 2) + binary;
        decimal = decimal / 2;
    }
    
    return binary;
}


string code_in_fibonacci(int decimal){

    int Fib[1000];
    Fib[0] = 1;
    Fib[1] = 2;

    if(decimal == 1){
        return "11";
    }
    else if(decimal == 2){
        return "011";
    }
    else{
        int i = 0;
        do{
            i++;
            Fib[i+1] = Fib[i] + Fib[i-1];
        } while(Fib[i+1] <= decimal);

        string code = "1";

        while(i >= 0){
            if(decimal >= Fib[i]){
                code = "1" + code;
                decimal = decimal - Fib[i];
            }
            else{
                code = "0" + code;
            }
            i--;
        }
        return code;
    }
}

string code_in_gamma(int decimal){

    string n_bin = decimal_to_binary(decimal); // zapisujemy decimal binarnie
    string code = string((n_bin.length() - 1), '0') + n_bin;
    // jesli k to liczba bitow decimal to na poczatku wpisujemy k - 1 razy 0 i dopisujemy decimal w systemie binarnej

    return code;
}

string code_in_delta(int decimal){

    string n_bin = decimal_to_binary(decimal); // zapisujemy decimal binarnie
    string prefix = code_in_gamma(n_bin.length()); // kodujemy gammą liczbę bitów decimal
    string n_cutet = n_bin.substr(1, (n_bin.length() - 1)); // postac binarna bez najabardziej znaczacego bita
    string code = prefix + n_cutet;

    return code;
}

string code_in_omega(int decimal){

    string code = "0";
    string n_bin = decimal_to_binary(decimal);
    int len;
    while(n_bin.length() > 1){
        code = n_bin + code;
        len = n_bin.length();
        n_bin = decimal_to_binary(len - 1);
    }

    return code;
}

// to run code pass name of input and output file as arguments
int main(int argc, char **argv)
{
    int code_type;
    cout<<"Wybierz rodzaj kodowania:\n"; 
    cout<<"1 - elias omega\n2 - elias delta\n3 - elias gamma\n4 - fibbonacci\n";
    cin >> code_type; 

    FILE *myfile;
    myfile = fopen(argv[2], "wb");

    FILE *f = freopen(argv[1], "rb", stdin);  

     
    
    basic_codes_to_dictionary(); // dodajemy ascii do slownika

    if (myfile)
    {
        int sym; // 8 bitowy znak pobierany z oryginalnego pliku
        string p = "", c = "";
        int index = 256;
        string code;
        string text = "";
        string bits_to_send;
        int number;
        

        sym = getchar();
        p = char(sym); // p jest charem np. 'a' , sym jest kodem ascii p np. '97'

        switch(code_type)
        {
        case 1:
            while ((sym = getchar()) != EOF)
            {
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    //cout << p << "\t" << dictionary[p] << "\t\t" << p + c << "\t" << index << endl;
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    code = code_in_omega(dictionary[p]+1); // kodujemy nasz indeks w kodzie omega
                    //cout << code; //<< "(" << dictionary[p] + 1 << ")_";
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        //number++; // Musimy wysyłać indeksy o jeden większe ponieważ wszytstkie kodowania zaczynają się od jedynki
                        fwrite(&number, 1, 1, myfile);
                        // cout << bits_to_send; // << "(" << number << ")_";
                        text = text.substr(8);
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            // musimy dopisać ostatni index do pliku
            //cout << p << "\t" << dictionary[p] << endl;
            
            code = code_in_omega(dictionary[p]+1);
            break;
        case 2:
            while ((sym = getchar()) != EOF)
            {
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    //cout << p << "\t" << dictionary[p] << "\t\t" << p + c << "\t" << index << endl;
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    code = code_in_delta(dictionary[p]+1); // kodujemy nasz indeks w kodzie omega
                    //cout << code; //<< "(" << dictionary[p] + 1 << ")_";
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        //number++; // Musimy wysyłać indeksy o jeden większe ponieważ wszytstkie kodowania zaczynają się od jedynki
                        fwrite(&number, 1, 1, myfile);
                        // cout << bits_to_send; // << "(" << number << ")_";
                        text = text.substr(8);
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            code = code_in_delta(dictionary[p]+1);
            break;
        case 3:
            while ((sym = getchar()) != EOF)
            {
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    
                    code = code_in_gamma(dictionary[p]+1); // kodujemy nasz indeks w kodzie omega
                    //cout << code; //<< "(" << dictionary[p] + 1 << ")_";
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        //number++; // Musimy wysyłać indeksy o jeden większe ponieważ wszytstkie kodowania zaczynają się od jedynki
                        fwrite(&number, 1, 1, myfile);
                        // cout << bits_to_send; // << "(" << number << ")_";
                        text = text.substr(8);
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            
            code = code_in_gamma(dictionary[p]+1);
            break;
        case 4:
            while ((sym = getchar()) != EOF)
            {
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    
                    code = code_in_fibonacci(dictionary[p]+1); // kodujemy nasz indeks w kodzie omega
                    //cout << code; //<< "(" << dictionary[p] + 1 << ")_";
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        //number++; // Musimy wysyłać indeksy o jeden większe ponieważ wszytstkie kodowania zaczynają się od jedynki
                        fwrite(&number, 1, 1, myfile);
                        // cout << bits_to_send; // << "(" << number << ")_";
                        text = text.substr(8);
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            
            code = code_in_fibonacci(dictionary[p]+1);
            break; 
        default:
            break;           
            
        }

        text = text + code;
        while(text.length() >= 8)
        {
            bits_to_send = text.substr(0, 8);
            number = binary_to_decimal(bits_to_send);
             //number++; // Musimy wysyłać indeksy o jeden większe ponieważ wszytstkie kodowania zaczynają się od jedynki
            fwrite(&number, 1, 1, myfile);
            // cout << bits_to_send; // << "(" << number << ")_";
            text = text.substr(8);
        }

        // Flush bits
        int ile_dopisac_0 = 8 - text.length();
        for (int i = 0; i < ile_dopisac_0; i++)
        {
            text = text + "0";
        }
        bits_to_send = text.substr(0, 8);
        number = binary_to_decimal(bits_to_send);
        //number++; // Musimy wysyłać indeksy o jeden większe ponieważ wszytstkie kodowania zaczynają się od jedynki
        fwrite(&number, 1, 1, myfile);
        // cout << bits_to_send; // << "(" << number << ")_";
        text = text.substr(8);
    }

    fclose(f);
    fclose(myfile);

    return 0;
}