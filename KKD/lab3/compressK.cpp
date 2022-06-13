#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

unordered_map<string, long int> dictionary; // structure to keep dictionary

long int out_size = 0; // size of file compressed
long int in_size = 0;


double table[256] = { 0.0 }; //tablica do entropii, zliczam dane znaki zaczynając od 0
double sum = 0.0; //ilosc wszystkich znaków
double entropy = 0.0; //szukana entropia
double vartropy = 0.0; //suma wewnetrzna we wzorze na entropie warunkową
double varintropy = 0.0; //cała entropia warunkowa - szukana
double prob = 0.0; //prawdopodobienstwo na dany symbol
double varprob = 0; //prawdopodobienstwo warunkow na symbol po symbolu
unsigned int znak; //ciąg 8 bitów
unsigned int previous = 0; //poprzedni ciąg
double vartab[256][256] = { 0.0 };//tablica do entropii war, zliczam ilosc wystapien symbolu po symbolu

// adding basic codes (ASCII) to dictionary (0-255)
void basic_codes_to_dictionary(){
    for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		dictionary[ch] = i;
	}
}

// covert decimal numbers in int to stribg of binary reprezantation
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


string fibonacci_coding(int decimal){

    int fib[1000];
    fib[0] = 1;
    fib[1] = 2;

    if(decimal == 1){
        return "11";
    }
    else if(decimal == 2){
        return "011";
    }
    else{
        int i = 0;
        do{ // parsing to array iteratively all(1000) fibonacci numbers
            i++;
            fib[i+1] = fib[i] + fib[i-1];
        } while(fib[i+1] <= decimal);

        string code = "1";

        // constructing codes
        while(i >= 0){
            if(decimal >= fib[i]){
                code = "1" + code;
                decimal = decimal - fib[i];
            }
            else{
                code = "0" + code;
            }
            i--;
        }
        return code;
    }
}

string gamma_coding(int decimal){

    string n_bin = decimal_to_binary(decimal); // passing int to bin string
    string code = string((n_bin.length() - 1), '0') + n_bin;
    // gamma code is k-1 of zeroes added at beginning of binary number, 
    // where k is length of binary number
    return code;
}

string delta_coding(int decimal){

    string n_bin = decimal_to_binary(decimal); // we write decimal binary
    string prefix = gamma_coding(n_bin.length()); // we use gamma to code that much zeroes as lenght of
                                                  // our number to code, then we give binary count of this  
    string n_cutet = n_bin.substr(1, (n_bin.length() - 1)); // binary rep without left bit
    string code = prefix + n_cutet;

    return code;
}

string omega_coding(int decimal){

    string code = "0"; // at left of number bit we always have 0
    string n_bin = decimal_to_binary(decimal);
    int len;
    while(n_bin.length() > 1){
        code = n_bin + code; // at 1st step we code binary our number, then
        len = n_bin.length();
        n_bin = decimal_to_binary(len - 1); //we code binary length-1 of binary till its 1 
    }

    return code;
}

// to run code pass name of input and output file as arguments
// important note: you should name your outupt file whith giving letter of coding at the and like:
//  myoutpytO.bin for omega coding or myoutpytF.bin for fibonacci coding, and ...D.bin, ...G.bin
int main(int argc, char **argv)
{
    int code_type; // which coding we use
    cout<<"Wybierz rodzaj kodowania:\n"; 
    cout<<"1 - elias omega\n2 - elias delta\n3 - elias gamma\n4 - fibbonacci\n";
    cin >> code_type; 

    const clock_t begin_time = clock(); // time measurement

    FILE *myfile; // output
    myfile = fopen(argv[2], "wb");

    FILE *f = freopen(argv[1], "rb", stdin);  // input 

     
    
    basic_codes_to_dictionary(); // dodajemy ascii do slownika

    if (myfile)
    {
        int sym; // we get 8 bits code from inmput file using getchar
        string p = "", c = "";
        int index = 256; // so we start after basic alphabet which is 0-255
        string code;
        string text = "";
        string bits_to_send;
        int number;
        

        sym = getchar();

        //entropy below--------------------------------------------------------
        ++vartab[previous][sym]; //incrementuję ilosc symboli po danym symbolu
        ++table[sym]; //incrementuję ilość danych symboli
        ++sum; //incr wszystkie symbole
        previous = sym; //oznaczam poprzedni symbol
        //-------------------------------------------------------------------------
        in_size++;
        p = char(sym); // p is char and sym is ascii code

        switch(code_type) // depending on coding type. only difference is encrypting code of LZW to elias or fib
        {
        case 1:
            while ((sym = getchar()) != EOF) // below is LZW algo
            {
                //entropy below----------------------------------------
                ++vartab[previous][sym]; //increment symbols after
                ++table[sym]; //incrementuję ilość danych symboli
                ++sum; //incr wszystkie symbole
                previous = sym; //oznaczam poprzedni symbol
                //-------------------------------------------------------

                in_size++;
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){ // we check if we already got specific code symbol
                    p = p + c; // if so, we construct new code by adding next char
                }
                else{
                    code = omega_coding(dictionary[p]+1); // we encrypt in omega our code to send
                    // p+1 cause we have no 0 in codings, so all shifted +1

                    text = text + code; //packing existing symbol-code to bigger buffer
                    while (text.length() >= 8) //code can have more than 8 bits, so we packaging it on 8bits only
                    {
                        bits_to_send = text.substr(0, 8); // we cut first 8 bits from our text to send
                        number = binary_to_decimal(bits_to_send); // translate string of binary to int
                        fwrite(&number, 1, 1, myfile); // writing byte representing piece of our code to file
                        out_size++; //size of file binary
                        text = text.substr(8); // rest of code, that was longer than 8bits
                    }
                    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            // we got one left code to add
            code = omega_coding(dictionary[p]+1);
            break;
        case 2:
            while ((sym = getchar()) != EOF)
            {
                ++vartab[previous][sym]; //incrementuję ilosc symboli po danym symbolu
                ++table[sym]; //incrementuję ilość danych symboli
                ++sum; //incr wszystkie symbole
                previous = sym; //oznaczam poprzedni symbol

                in_size++;
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    code = delta_coding(dictionary[p]+1);
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        out_size++;
                        text = text.substr(8);
                    }
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            code = delta_coding(dictionary[p]+1);
            break;
        case 3:
            while ((sym = getchar()) != EOF)
            {
                ++vartab[previous][sym]; //incrementuję ilosc symboli po danym symbolu
                ++table[sym]; //incrementuję ilość danych symboli
                ++sum; //incr wszystkie symbole
                previous = sym; //oznaczam poprzedni symbol
                
                in_size++;
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    
                    code = gamma_coding(dictionary[p]+1); 
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        out_size++;
                        text = text.substr(8);
                    }
                    dictionary[p + c] = index; //this new string-symbol-code is signet on next int value of dict - over 255 to inf?
                    index++; //new index in dictionary
                    p = c;
                }
                c = "";
            }
            
            code = gamma_coding(dictionary[p]+1);
            break;
        case 4:
            while ((sym = getchar()) != EOF)
            {
                ++vartab[previous][sym]; //incrementuję ilosc symboli po danym symbolu
                ++table[sym]; //incrementuję ilość danych symboli
                ++sum; //incr wszystkie symbole
                previous = sym; //oznaczam poprzedni symbol

                in_size++;
                c = char(sym);

                if (dictionary.find(p + c) != dictionary.end()){
                    p = p + c;
                }
                else{
                    code = fibonacci_coding(dictionary[p]+1); 
                    text = text + code;
                    while (text.length() >= 8)
                    {
                        bits_to_send = text.substr(0, 8);
                        number = binary_to_decimal(bits_to_send);
                        fwrite(&number, 1, 1, myfile);
                        out_size++;
                        text = text.substr(8);
                    }
                    dictionary[p + c] = index;
                    index++;
                    p = c;
                }
                c = "";
            }
            
            code = fibonacci_coding(dictionary[p]+1);
            break; 
        default:
            break;           
            
        }

        // leftover
        text = text + code;
        while(text.length() >= 8)
        {
            bits_to_send = text.substr(0, 8);
            number = binary_to_decimal(bits_to_send);
            fwrite(&number, 1, 1, myfile);
            out_size++;
            text = text.substr(8);
        }

        // Flush bits
        int flush_zeroes = 8 - text.length();
        for (int i = 0; i < flush_zeroes; i++)
        {
            text = text + "0";
        }
        bits_to_send = text.substr(0, 8);
        number = binary_to_decimal(bits_to_send);
        fwrite(&number, 1, 1, myfile);
        out_size++;
        text = text.substr(8);
    }

    fclose(f);
    fclose(myfile);

    const clock_t end_time = clock();

    for (int i = 0; i < 256; i++)
    {
        if(table[i] != 0) {
            //prob = table[i] / sum; //P(A)
            entropy = entropy + ((table[i]) * ((log2(table[i])) - log2(sum))); //prob * i(A)
            //cout<<"entropia: "<<entropy<<endl;

            // cout << "znak nr " << i << ": " << table[i] << endl;

            for (int j = 0; j < 256; j++) {
                if (vartab[i][j] != 0 && table[i] != 0) {
                    //varprob = vartab[i][j] / table[i];
                    varintropy =
                            varintropy + ((vartab[i][j]) * ((log2(vartab[i][j]) - log2(table[i])))); //wewnętrzna suma
                }
            }

            varintropy = varintropy / table[i];

            prob = table[i] / sum; //P(A)
            vartropy = vartropy + (prob * varintropy); //szukana entropia warunkowa
            varintropy = 0.0; //po iteracji wewnętrznej sumy ją zeruję
        }
    }

    entropy = (entropy * (-1) / sum);
    vartropy = vartropy * (-1);
    printf("suma: %2.10f", sum);
    cout<<endl;
    //cout<<"entropia1: "<<entropy<<endl;
    printf("entropia: %2.20f", entropy);
    cout<<endl;
    //cout<<"vartropia1: "<<vartropy<<endl;
    printf("vartropia: %2.20f", vartropy); //zwiekszyć precyzje wyswietlania
    cout<<endl;    

    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;

    cout<<"wielkosc (bajty) pliku wejsciowego: "<<in_size<<endl;
    cout<<"wielkosc (bajty) pliku wyjsciowego: "<<out_size<<endl;
    cout<<"czas kompresowania: "<<dur<<endl;

    return 0;
}