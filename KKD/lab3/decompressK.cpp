#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

unordered_map<int, string> table;

void basic_codes_to_dict(){
    for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
}

int fibb_decode(string input){

    int x, y, z;
    x = 1;
    y = 2;

    int n = 0;

    if(input == "11")
        return 1;
    
    if(input == "011")
        return 2;
    
    if(input[0] == '1')
        n = n + 1;

    if(input[1] == '1')
        n = n + 2;

    int i = 2;
    while(input[i] != '1' || input[i+1] != '1'){

        z = x + y;
        x = y;
        y = z;
        
        if(input[i] == '1')
        {
            n = n + z;
        }
        i++;
    }
    z = x + y; 
    n = n + z;
    return n; 
}

int binary_to_decimal(string bin)
{
    int dec = 0;
    for (size_t i = 0; i < bin.length(); i++)
    {
        if (bin[i] == '1')
        {
            dec = dec + pow(2, (bin.length() - i - 1));
        }
    }
    return dec;
}

// function to convert decimal to binary
string decimal_to_binary(int n)
{
    string binary = "";

    int binaryNum[32];

    int i = 0;
    while (n > 0)
    {
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int z = 0; z < 8 - i; z++)
    {
        binary = binary + "0";
    }

    for (int j = i - 1; j >= 0; j--)
        binary = binary + to_string(binaryNum[j]);

    return binary;
}

void decoding(vector<int> op, ofstream &out)
{
	cout << "\nDecoding\n";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0], n;
	string s = table[old];
	string c = "";
	c += s[0];
	// cout << s;
    out << s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (table.find(n) == table.end()) {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
        out << s; //writting to file our strings
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
}

int main(int argc, char **argv)
{

    const clock_t begin_time = clock();

    vector<int> decoded_to_lzw;
    char type;
    FILE *f = freopen(argv[1], "rb", stdin);
    
    type = argv[1][sizeof(argv[1]) - 6];
    cout<< "oto: "<<type<<endl;

    basic_codes_to_dict();

    int sym; // 8 bitowy znak pobierany z oryginalnego pliku
    string package_bits = ""; 
    int n, k, p, x, y, z;
    string number = "";
    string code = "";
    
    

    // ofstream out("output.txt");
    switch(type)
    {
        case 'O':
            n = 1;
            while ((sym = getchar()) != EOF)
            {
                package_bits = package_bits + decimal_to_binary(sym);
                 
                while(n+1 <= package_bits.length() && package_bits[0] != '0')
                {
                    number = package_bits.substr(0,n+1); 
                    package_bits = package_bits.substr(n+1);
                    n = binary_to_decimal(number);
                }
                if(package_bits[0] == '0'){
                    n--; // decreasing by 1, due to no 0 problem in codings
                    
                    decoded_to_lzw.push_back(n);

                    n = 1;
                    package_bits = package_bits.substr(1); // cutting added 0 bit
                }
            }
            break;

        case 'D':
            
            while ((sym = getchar()) != EOF)
            {
                k = 1;
                n = 0;
                p = 0;
                package_bits = package_bits + decimal_to_binary(sym);
                
                while(package_bits[0] == '0')
                {
                    k++;
                    package_bits = package_bits.substr(1);
                }

                while(k > package_bits.size()){
                    sym = getchar();
                    package_bits = package_bits + decimal_to_binary(sym);

                }
                
                number = package_bits.substr(0, k);
                package_bits = package_bits.substr(k);
                n = binary_to_decimal(number);
                n--;

                while(n > package_bits.size()){
                    sym = getchar();
                    package_bits = package_bits + decimal_to_binary(sym);

                }

                code = package_bits.substr(0,n);
                package_bits = package_bits. substr(n);
                
                code = '1' + code;

                p = binary_to_decimal(code);
                p--; // decreasing code by 1, cause it was increased before

                decoded_to_lzw.push_back(p);
                
                
            }
            break;  

        case 'G':
            while ((sym = getchar()) != EOF)
            {
                k = 1;
                
                package_bits = package_bits + decimal_to_binary(sym);
                
                while(package_bits[0] == '0') // counting amount of zeroes
                {
                    k++;
                    package_bits = package_bits.substr(1);
                    if(package_bits == ""){
                        sym = getchar();
                        package_bits = package_bits + decimal_to_binary(sym);
                    }
                }

                while(k > package_bits.size()){
                    sym = getchar();
                    package_bits = package_bits + decimal_to_binary(sym);

                }
                
                number = package_bits.substr(0, k);
                package_bits = package_bits.substr(k);
                n = binary_to_decimal(number);
                n--;

                decoded_to_lzw.push_back(n);
                
                
            }
            break; 

        case 'F':
            k = 1;
            while ((sym = getchar()) != EOF)
            {
                
                
                
                package_bits = package_bits + decimal_to_binary(sym);

                while(k < package_bits.length() && (package_bits[k] != '1' || package_bits[k - 1] != '1')){
                k++;            
                }
                
                if(package_bits[k] == '1' && package_bits[k-1] == '1'){
                    number = package_bits.substr(0,k+1);
                    package_bits = package_bits.substr(k+1);
                    n = fibb_decode(number) - 1; // cause it was shifted right
                    decoded_to_lzw.push_back(n);
                    k = 1;
                }

            }    

            break;       

        default:
            cout << "ciba\n";
            break;    
    }    
    // out.close();
    fclose(f);

    ofstream out (argv[2]);
    //cout<<"dupa1\n";
    decoding(decoded_to_lzw, out);
    //cout<<"dupa1\n";
    out.close();

    const clock_t end_time = clock();
    float dur = float( end_time - begin_time ) /  CLOCKS_PER_SEC;
    cout<<"czas dekompresowania: "<<dur<<endl;


    return 0;
}
