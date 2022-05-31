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

long double p1_tab_b[256] = { 0.0 };
long double p1_tab_g[256] = { 0.0 };
long double p1_tab_r[256] = { 0.0 };
long double p1_tab_all[256] = { 0.0 };

long double p2_tab_b[256] = { 0.0 };
long double p2_tab_g[256] = { 0.0 };
long double p2_tab_r[256] = { 0.0 };
long double p2_tab_all[256] = { 0.0 };

long double p3_tab_b[256] = { 0.0 };
long double p3_tab_g[256] = { 0.0 };
long double p3_tab_r[256] = { 0.0 };
long double p3_tab_all[256] = { 0.0 };

long double p4_tab_b[256] = { 0.0 };
long double p4_tab_g[256] = { 0.0 };
long double p4_tab_r[256] = { 0.0 };
long double p4_tab_all[256] = { 0.0 };

long double p5_tab_b[256] = { 0.0 };
long double p5_tab_g[256] = { 0.0 };
long double p5_tab_r[256] = { 0.0 };
long double p5_tab_all[256] = { 0.0 };

long double p6_tab_b[256] = { 0.0 };
long double p6_tab_g[256] = { 0.0 };
long double p6_tab_r[256] = { 0.0 };
long double p6_tab_all[256] = { 0.0 };

long double p7_tab_b[256] = { 0.0 };
long double p7_tab_g[256] = { 0.0 };
long double p7_tab_r[256] = { 0.0 };
long double p7_tab_all[256] = { 0.0 };

long double p8_tab_b[256] = { 0.0 };
long double p8_tab_g[256] = { 0.0 };
long double p8_tab_r[256] = { 0.0 };
long double p8_tab_all[256] = { 0.0 };

long double smallest_entropy(long double e0, long double e1, long double e2, long double e3, long double e4, long double e5, long double e6, long double e7, long double e8){

    long double current_smallest;
    current_smallest = min(e0,e1);
    current_smallest = min(current_smallest,e2);
    current_smallest = min(current_smallest,e3);
    current_smallest = min(current_smallest,e4);
    current_smallest = min(current_smallest,e5);
    current_smallest = min(current_smallest,e6);
    current_smallest = min(current_smallest,e7);
    current_smallest = min(current_smallest,e8);
    return current_smallest;
}

void best_predyktor(long double e0, long double e1, long double e2, long double e3, long double e4, long double e5, long double e6, long double e7, long double e8){

    
    long double best_entropy = smallest_entropy(e0,e1,e2,e3,e4,e5,e6,e7,e8);
    printf("Najmniejsza entropia = %.20Lf \nSposób kodowania: ", best_entropy);

    if(best_entropy == e0)
        cout << "original" << endl;
    else if (best_entropy == e1)
        cout << "predyktor 1" << endl;
    else if (best_entropy == e2)
        cout << "predyktor 2" << endl;
    else if (best_entropy == e3)
        cout << "predyktor 3" << endl;
    else if (best_entropy == e4)
        cout << "predyktor 4" << endl;
    else if (best_entropy == e5)
        cout << "predyktor 5" << endl;
    else if (best_entropy == e6)
        cout << "predyktor 6" << endl;    
    else if (best_entropy == e7)
        cout << "predyktor 7" << endl;
    else if (best_entropy == e8)
        cout << "predyktor 8" << endl;

    cout << endl;
}


int modulo(int x, int y){
    int z = x%y;
    if (z >= 0){
        return z;
    }
    else{
        return y + z;
    }
}

int pred8(int NW, int N, int W){
    if (NW >= max(N, W)){
        return min(W, N);
    }
    else if (NW <= min(W, N)){
        return max(W, N);
    }
    else{
        return modulo((W + N - NW), 256);
    }
}

int pred7(int N, int W){
    return (N + W) / 2;
}

int pred6(int NW, int N, int W){
    return modulo(W + (N - NW)/2, 256);
}

int pred5(int NW, int N, int W){
    return modulo(N + (W - NW)/2, 256);
}

int pred4(int NW, int N, int W){
    return modulo(W + N - NW, 256);
}

int pred3(int NW){
    return NW;
}

int pred2(int N){
    return N;
}

int pred1(int W){
    return W;
}



void codings(int NW, int N, int W, int sym, int color){
    int x;
    switch(color){
        case 1:
            x = pred1(W);
            p1_tab_all[modulo((sym - x), 256)]++;
            p1_tab_b[modulo((sym - x), 256)]++;
            x = pred2(N);
            p2_tab_all[modulo((sym - x), 256)]++;
            p2_tab_b[modulo((sym - x), 256)]++;
            x = pred3(NW);
            p3_tab_all[modulo((sym - x), 256)]++;
            p3_tab_b[modulo((sym - x), 256)]++;
            x = pred4(NW, N, W);
            p4_tab_all[modulo((sym - x), 256)]++;
            p4_tab_b[modulo((sym - x), 256)]++;
            x = pred5(NW, N, W);
            p5_tab_all[modulo((sym - x), 256)]++;
            p5_tab_b[modulo((sym - x), 256)]++;
            x = pred6(NW, N, W);
            p6_tab_all[modulo((sym - x), 256)]++;
            p6_tab_b[modulo((sym - x), 256)]++;
            x = pred7(N, W);
            p7_tab_all[modulo((sym - x), 256)]++;
            p7_tab_b[modulo((sym - x), 256)]++;
            x = pred8(NW, N, W);
            p8_tab_all[modulo((sym - x), 256)]++;
            p8_tab_b[modulo((sym - x), 256)]++;
            break;
        case 2:
            x = pred1(W);
            p1_tab_all[modulo((sym - x), 256)]++;
            p1_tab_g[modulo((sym - x), 256)]++;
            x = pred2(N);
            p2_tab_all[modulo((sym - x), 256)]++;
            p2_tab_g[modulo((sym - x), 256)]++;
            x = pred3(NW);
            p3_tab_all[modulo((sym - x), 256)]++;
            p3_tab_g[modulo((sym - x), 256)]++;
            x = pred4(NW, N, W);
            p4_tab_all[modulo((sym - x), 256)]++;
            p4_tab_g[modulo((sym - x), 256)]++;
            x = pred5(NW, N, W);
            p5_tab_all[modulo((sym - x), 256)]++;
            p5_tab_g[modulo((sym - x), 256)]++;
            x = pred6(NW, N, W);
            p6_tab_all[modulo((sym - x), 256)]++;
            p6_tab_g[modulo((sym - x), 256)]++;
            x = pred7(N, W);
            p7_tab_all[modulo((sym - x), 256)]++;
            p7_tab_g[modulo((sym - x), 256)]++;
            x = pred8(NW, N, W);
            p8_tab_all[modulo((sym - x), 256)]++;
            p8_tab_g[modulo((sym - x), 256)]++;
            break;
        case 3:
            x = pred1(W);
            p1_tab_all[modulo((sym - x), 256)]++;
            p1_tab_r[modulo((sym - x), 256)]++;
            x = pred2(N);
            p2_tab_all[modulo((sym - x), 256)]++;
            p2_tab_r[modulo((sym - x), 256)]++;
            x = pred3(NW);
            p3_tab_all[modulo((sym - x), 256)]++;
            p3_tab_r[modulo((sym - x), 256)]++;
            x = pred4(NW, N, W);
            p4_tab_all[modulo((sym - x), 256)]++;
            p4_tab_r[modulo((sym - x), 256)]++;
            x = pred5(NW, N, W);
            p5_tab_all[modulo((sym - x), 256)]++;
            p5_tab_r[modulo((sym - x), 256)]++;
            x = pred6(NW, N, W);
            p6_tab_all[modulo((sym - x), 256)]++;
            p6_tab_r[modulo((sym - x), 256)]++;
            x = pred7(N, W);
            p7_tab_all[modulo((sym - x), 256)]++;
            p7_tab_r[modulo((sym - x), 256)]++;
            x = pred8(NW, N, W);
            p8_tab_all[modulo((sym - x), 256)]++;
            p8_tab_r[modulo((sym - x), 256)]++;
            break;  
        default:
            cout<<"dupcia"<<endl;
            break;      
    }


}

int main(int argc, char **argv){


    //entropies initialization----------------------------------------------------------------
    long double bluetropy = 0.0; // basic entopies, before codings
    long double greentropy = 0.0; 
    long double redtropy = 0.0;  
    long double alltropy = 0.0;

    long double p1_bluetropy = 0.0; // entropies for different predikates
    long double p1_greentropy = 0.0; 
    long double p1_redtropy = 0.0;  
    long double p1_alltropy = 0.0;

    long double p2_bluetropy = 0.0; 
    long double p2_greentropy = 0.0; 
    long double p2_redtropy = 0.0;  
    long double p2_alltropy = 0.0;

    long double p3_bluetropy = 0.0; 
    long double p3_greentropy = 0.0; 
    long double p3_redtropy = 0.0;  
    long double p3_alltropy = 0.0;

    long double p4_bluetropy = 0.0; 
    long double p4_greentropy = 0.0; 
    long double p4_redtropy = 0.0;  
    long double p4_alltropy = 0.0;

    long double p5_bluetropy = 0.0; 
    long double p5_greentropy = 0.0; 
    long double p5_redtropy = 0.0;  
    long double p5_alltropy = 0.0;

    long double p6_bluetropy = 0.0; 
    long double p6_greentropy = 0.0; 
    long double p6_redtropy = 0.0;  
    long double p6_alltropy = 0.0;

    long double p7_bluetropy = 0.0; 
    long double p7_greentropy = 0.0; 
    long double p7_redtropy = 0.0;  
    long double p7_alltropy = 0.0;

    long double p8_bluetropy = 0.0; 
    long double p8_greentropy = 0.0; 
    long double p8_redtropy = 0.0;  
    long double p8_alltropy = 0.0;
    //---------------------------------------------------------------------------------------

    // getting information from binary file--------------------------------------------------
    int sym; // to get 1 byte
    int sym_1; // first byte if we have to get two bytes
    int sym_2; // second byte if we have to get two bytes
    // number on two bytes is like we do :
    // sym_1 = getchar();
    // sym_2 = getchar();
    // sym = sym_1 * 256 + sym_2;
    //----------------------------------------------------------------------------------------
    
    //specific information from header--------------------------------------------------------
    int F1; // number of bits in F6  || size: 1 byte
    int F2; // define if F7 exist. It is 0 or 1 || size: 1 byte
    int F3; // || size: 1 byte
    int F4_1; // starting entry in color map || size: 2 bytes
    int F4_2; // color map length - number of entries || size: 2 bytes
    int F4_3; // color map entry size - bits per entry || size: 1 byte || ex: 15, 16, 24, 32
    // F4_3 * F4_2 define size of F7
    int F5_1; // spawn X || size: 2 bytes
    int F5_2; // spawn Y || size: 2 bytes
    int F5_3; // image width || size: 2 bytes
    int F5_4; // image height || size: 2 bytes
    int F5_5; // pixel depth - how many bits per pixel. f.e. 24 || size: 1 byte
    uint8_t F5_6; // descriptor - bit 4: left-right, bit 5: top-bottom || size: 1 byte
    int order; // this is 4th and 5th bit of F5_6
    uint8_t help_operator = 48;
    // till now we have 18 bits written and that is all of header
    // in our list we assume, that F6 and F7 not exist

    int F6; // image ID. || size: F1 bytes. if 0, F6 not exist
    int F7; // color map data. F2 must be 1. || size: F4_2 * F4_3 / 8 (NOT SURE YET)

    
    FILE *f = freopen(argv[1], "rb", stdin);  // input

    // next we read our image
    if(f){

        F1 = getchar();
        F2 = getchar();
        F3 = getchar();

        sym_1 = getchar();
        sym_2 = getchar();
        F4_1 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F4_2 = sym_1  + sym_2 * 256;

        F4_3 = getchar();

        sym_1 = getchar();
        sym_2 = getchar();
        F5_1 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F5_2 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F5_3 = sym_1  + sym_2 * 256;

        sym_1 = getchar();
        sym_2 = getchar();
        F5_4 = sym_1  + sym_2 * 256;

        F5_5 = getchar();
        F5_6 = getchar();

        order = F5_6 & help_operator;
        //  __ __ ____   &  00 11 0000

        


    }

    // print info from header:
    cout<<"F1: "<<F1<<endl;
    cout<<"F2: "<<F2<<endl;
    cout<<"F3: "<<F3<<endl;
    cout<<"F4_1: "<<F4_1<<endl;
    cout<<"F4_2: "<<F4_2<<endl;
    cout<<"F4_3: "<<F4_3<<endl;
    cout<<"F5_1 - X spawn: "<<F5_1<<endl;
    cout<<"F5_2 - Y spawn: "<<F5_2<<endl;
    cout<<"F5_3 - image width: "<<F5_3<<endl;
    cout<<"F5_4 - image height: "<<F5_4<<endl;
    cout<<"F5_5 - pixel depth: "<<F5_5<<endl;
    cout<<"F5_6 - descriptor: "<<F5_6<<endl;
    cout<<"order: ";
    switch(order){
        case 0:
            cout<<order<<" (left-bottom)"<<endl;
            break;
        case 16:
            cout<<order<<" (right-bottom)"<<endl;
            break;
        case 32:
            cout<<order<<" (left-top)"<<endl;  
            break;
        case 48:
            cout<<order<<" (right-top)"<<endl;      
            break;
        default:
            cout<<order<<" fault"<<endl;
            break;    
        

    }

    // reading IMAGE DATA SECTION (F8)----------------
    // our order is left-bottom

    int color_blocks = F5_5 / 3; // in this ex it is 3
    int red, green, blue;
    int N_b, NW_b, W_b, N_g, NW_g, W_g, N_r, NW_r, W_r, curr;
    int width = F5_3;
    int height = F5_4;
    int x;
    long double pixels = width * height;
    long double all_bytes = pixels * 3;

    long double tab_b[256] = { 0.0 };
    long double tab_g[256] = { 0.0 };
    long double tab_r[256] = { 0.0 };
    long double tab_all[256] = { 0.0 };

    int row_blue_north[width + 1];
    row_blue_north[0] = 0;

    int row_green_north[width + 1];
    row_green_north[0] = 0;
    
    int row_red_north[width + 1];
    row_red_north[0] = 0;

    
    int row_blue_curr[width + 1];
    row_blue_curr[0] = 0;
    
    int row_green_curr[width + 1];
    row_green_curr[0] = 0;

    int row_red_curr[width + 1];
    row_red_curr[0] = 0;

    // reading IMAGE ID and counting entropies and coding--------------------------------------------------------------------
    for (int i = 1; i <= width; i++ ){
            sym = getchar();
            row_blue_curr[i] = sym;
            tab_b[sym]++;
            tab_all[sym]++;

            sym = getchar();
            row_green_curr[i] = sym;
            tab_g[sym]++;
            tab_all[sym]++;

            sym = getchar();
            row_red_curr[i] = sym;
            tab_r[sym]++;
            tab_all[sym]++;
        }


    for(int j = 2; j <= height; j++){

        for (int i = 1; i <= width; i++ ){
            // -------------------------------blue
            sym = getchar();
            row_blue_north[i] = sym;
            tab_b[sym]++;
            tab_all[sym]++;

            NW_b = row_blue_north[i-1];
            N_b = row_blue_north[i];
            W_b = row_blue_curr[i-1]; // wschód z x
            curr = row_blue_curr[i];  // mój x

            codings(NW_b, N_b, W_b, curr, 1);
            
            //row_blue_curr[i] = row_blue_north[i];
            
            
            //copy(row_blue_north, row_blue_north + width + 1, row_blue_curr);
            // -------------------------------green
            sym = getchar();
            row_green_north[i] = sym; 
            tab_g[sym]++;
            tab_all[sym]++;

            NW_g = row_green_north[i-1];
            N_g = row_green_north[i];
            W_g = row_green_curr[i-1];
            curr = row_green_curr[i];

            codings(NW_g, N_g, W_g, curr, 2);
            
            //row_green_curr[i] = row_green_north[i];
            
            //copy(row_green_north, row_green_north + width + 1, row_green_curr);
            // -------------------------------red
            sym = getchar();
            row_red_north[i] = sym;
            tab_r[sym]++;
            tab_all[sym]++;

            NW_r = row_red_north[i-1];
            N_r = row_red_north[i];
            W_r = row_red_curr[i-1];
            curr = row_red_curr[i];

            codings(NW_r, N_r, W_r, curr, 3);
            
            //row_red_curr[i] = row_red_north[i];
            

            //copy(row_red_north, row_red_north + width + 1, row_red_curr);
        }

        for (int k = 1; k <= width; k++){
            row_blue_curr[k] = row_blue_north[k];
            row_green_curr[k] = row_green_north[k];
            row_red_curr[k] = row_red_north[k];
        }
        
    }

    for (int i = 1; i <= width; i++ ){
        W_b = row_blue_curr[i-1];
        codings(0, 0, W_b, row_blue_curr[i], 1);
        W_g = row_green_curr[i-1];
        codings(0, 0, W_g, row_green_curr[i], 2);
        W_r = row_red_curr[i-1];
        codings(0, 0, W_r, row_red_curr[i], 3);
        
    }

    // -------------------------------------------------------------------------------------------------------------------


    // f.close();
    
    for (int i = 0; i < 256; i++){
        if(tab_all[i] != 0) {
            alltropy = alltropy + ((tab_all[i]) * ((log2(tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(tab_b[i] != 0) {
            bluetropy = bluetropy + ((tab_b[i]) * ((log2(tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(tab_g[i] != 0) {
            greentropy = greentropy + ((tab_g[i]) * ((log2(tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(tab_r[i] != 0) {
            redtropy = redtropy + ((tab_r[i]) * ((log2(tab_r[i])) - log2(pixels))); //prob * i(A)
        }       
        //--------------------pred1
        if(p1_tab_all[i] != 0) {
            p1_alltropy = p1_alltropy + ((p1_tab_all[i]) * ((log2(p1_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p1_tab_b[i] != 0) {
            p1_bluetropy = p1_bluetropy + ((p1_tab_b[i]) * ((log2(p1_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p1_tab_g[i] != 0) {
            p1_greentropy = p1_greentropy + ((p1_tab_g[i]) * ((log2(p1_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p1_tab_r[i] != 0) {
            p1_redtropy = p1_redtropy + ((p1_tab_r[i]) * ((log2(p1_tab_r[i])) - log2(pixels))); //prob * i(A)
        } 
        //--------------------pred2
        if(p2_tab_all[i] != 0) {
            p2_alltropy = p2_alltropy + ((p2_tab_all[i]) * ((log2(p2_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p2_tab_b[i] != 0) {
            p2_bluetropy = p2_bluetropy + ((p2_tab_b[i]) * ((log2(p2_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p2_tab_g[i] != 0) {
            p2_greentropy = p2_greentropy + ((p2_tab_g[i]) * ((log2(p2_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p2_tab_r[i] != 0) {
            p2_redtropy = p2_redtropy + ((p2_tab_r[i]) * ((log2(p2_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //--------------------pred3
        if(p3_tab_all[i] != 0) {
            p3_alltropy = p3_alltropy + ((p3_tab_all[i]) * ((log2(p3_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p3_tab_b[i] != 0) {
            p3_bluetropy = p3_bluetropy + ((p3_tab_b[i]) * ((log2(p3_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p3_tab_g[i] != 0) {
            p3_greentropy = p3_greentropy + ((p3_tab_g[i]) * ((log2(p3_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p3_tab_r[i] != 0) {
            p3_redtropy = p3_redtropy + ((p3_tab_r[i]) * ((log2(p3_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //--------------------pred4
        if(p4_tab_all[i] != 0) {
            p4_alltropy = p4_alltropy + ((p4_tab_all[i]) * ((log2(p4_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p4_tab_b[i] != 0) {
            p4_bluetropy = p4_bluetropy + ((p4_tab_b[i]) * ((log2(p4_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p4_tab_g[i] != 0) {
            p4_greentropy = p4_greentropy + ((p4_tab_g[i]) * ((log2(p4_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p4_tab_r[i] != 0) {
            p4_redtropy = p4_redtropy + ((p4_tab_r[i]) * ((log2(p4_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //--------------------pred5
        if(p5_tab_all[i] != 0) {
            p5_alltropy = p5_alltropy + ((p5_tab_all[i]) * ((log2(p5_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p5_tab_b[i] != 0) {
            p5_bluetropy = p5_bluetropy + ((p5_tab_b[i]) * ((log2(p5_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p5_tab_g[i] != 0) {
            p5_greentropy = p5_greentropy + ((p5_tab_g[i]) * ((log2(p5_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p5_tab_r[i] != 0) {
            p5_redtropy = p5_redtropy + ((p5_tab_r[i]) * ((log2(p5_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //--------------------pred6
        if(p6_tab_all[i] != 0) {
            p6_alltropy = p6_alltropy + ((p6_tab_all[i]) * ((log2(p6_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p6_tab_b[i] != 0) {
            p6_bluetropy = p6_bluetropy + ((p6_tab_b[i]) * ((log2(p6_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p6_tab_g[i] != 0) {
            p6_greentropy = p6_greentropy + ((p6_tab_g[i]) * ((log2(p6_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p6_tab_r[i] != 0) {
            p6_redtropy = p6_redtropy + ((p6_tab_r[i]) * ((log2(p6_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //-----------------pred7
        if(p7_tab_all[i] != 0) {
            p7_alltropy = p7_alltropy + ((p7_tab_all[i]) * ((log2(p7_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p7_tab_b[i] != 0) {
            p7_bluetropy = p7_bluetropy + ((p7_tab_b[i]) * ((log2(p7_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p7_tab_g[i] != 0) {
            p7_greentropy = p7_greentropy + ((p7_tab_g[i]) * ((log2(p7_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p7_tab_r[i] != 0) {
            p7_redtropy = p7_redtropy + ((p7_tab_r[i]) * ((log2(p7_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
        //------------------pred8
        if(p8_tab_all[i] != 0) {
            p8_alltropy = p8_alltropy + ((p8_tab_all[i]) * ((log2(p8_tab_all[i])) - log2(all_bytes))); //prob * i(A)
        }

        if(p8_tab_b[i] != 0) {
            p8_bluetropy = p8_bluetropy + ((p8_tab_b[i]) * ((log2(p8_tab_b[i])) - log2(pixels))); //prob * i(A)
        }

        if(p8_tab_g[i] != 0) {
            p8_greentropy = p8_greentropy + ((p8_tab_g[i]) * ((log2(p8_tab_g[i])) - log2(pixels))); //prob * i(A)
        }

        if(p8_tab_r[i] != 0) {
            p8_redtropy = p8_redtropy + ((p8_tab_r[i]) * ((log2(p8_tab_r[i])) - log2(pixels))); //prob * i(A)
        }
    }    

    

    alltropy = (alltropy * (-1) / all_bytes);
    bluetropy = (bluetropy * (-1) / pixels);
    greentropy = (greentropy * (-1) / pixels);
    redtropy = (redtropy * (-1) / pixels);

    p1_alltropy = (p1_alltropy * (-1) / all_bytes);
    p1_bluetropy = (p1_bluetropy * (-1) / pixels);
    p1_greentropy = (p1_greentropy * (-1) / pixels);
    p1_redtropy = (p1_redtropy * (-1) / pixels);

    p2_alltropy = (p2_alltropy * (-1) / all_bytes);
    p2_bluetropy = (p2_bluetropy * (-1) / pixels);
    p2_greentropy = (p2_greentropy * (-1) / pixels);
    p2_redtropy = (p2_redtropy * (-1) / pixels);

    p3_alltropy = (p3_alltropy * (-1) / all_bytes);
    p3_bluetropy = (p3_bluetropy * (-1) / pixels);
    p3_greentropy = (p3_greentropy * (-1) / pixels);
    p3_redtropy = (p3_redtropy * (-1) / pixels);

    p4_alltropy = (p4_alltropy * (-1) / all_bytes);
    p4_bluetropy = (p4_bluetropy * (-1) / pixels);
    p4_greentropy = (p4_greentropy * (-1) / pixels);
    p4_redtropy = (p4_redtropy * (-1) / pixels);

    p5_alltropy = (p5_alltropy * (-1) / all_bytes);
    p5_bluetropy = (p5_bluetropy * (-1) / pixels);
    p5_greentropy = (p5_greentropy * (-1) / pixels);
    p5_redtropy = (p5_redtropy * (-1) / pixels);

    p6_alltropy = (p6_alltropy * (-1) / all_bytes);
    p6_bluetropy = (p6_bluetropy * (-1) / pixels);
    p6_greentropy = (p6_greentropy * (-1) / pixels);
    p6_redtropy = (p6_redtropy * (-1) / pixels);

    p7_alltropy = (p7_alltropy * (-1) / all_bytes);
    p7_bluetropy = (p7_bluetropy * (-1) / pixels);
    p7_greentropy = (p7_greentropy * (-1) / pixels);
    p7_redtropy = (p7_redtropy * (-1) / pixels);

    p8_alltropy = (p8_alltropy * (-1) / all_bytes);
    p8_bluetropy = (p8_bluetropy * (-1) / pixels);
    p8_greentropy = (p8_greentropy * (-1) / pixels);
    p8_redtropy = (p8_redtropy * (-1) / pixels);
    cout<<"\n-------------------------------------------";
    cout<<"\npodstawowa entropia: "<<endl;
    printf("___alltropy:   %.20Lf", alltropy);
    cout<<endl;
    printf("___bluetropy:  %.20Lf", bluetropy);
    cout<<endl;
    printf("___greentropy: %.20Lf", greentropy);
    cout<<endl;
    printf("___redtropy:   %.20Lf", redtropy);
    cout<<endl;


    cout<<"\nwyniki dla predykatora 1: "<<endl;
    printf("p1_alltropy:   %.20Lf", p1_alltropy);
    cout<<endl;
    printf("p1_bluetropy:  %.20Lf", p1_bluetropy);
    cout<<endl;
    printf("p1_greentropy: %.20Lf", p1_greentropy);
    cout<<endl;
    printf("p1_redtropy:   %.20Lf", p1_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 2: "<<endl;
    printf("p2_alltropy:   %.20Lf", p2_alltropy);
    cout<<endl;
    printf("p2_bluetropy:  %.20Lf", p2_bluetropy);
    cout<<endl;
    printf("p2_greentropy: %.20Lf", p2_greentropy);
    cout<<endl;
    printf("p2_redtropy:   %.20Lf", p2_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 3: "<<endl;
    printf("p3_alltropy:   %.20Lf", p3_alltropy);
    cout<<endl;
    printf("p3_bluetropy:  %.20Lf", p3_bluetropy);
    cout<<endl;
    printf("p3_greentropy: %.20Lf", p3_greentropy);
    cout<<endl;
    printf("p3_redtropy:   %.20Lf", p3_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 4: "<<endl;
    printf("p4_alltropy:   %.20Lf", p4_alltropy);
    cout<<endl;
    printf("p4_bluetropy:  %.20Lf", p4_bluetropy);
    cout<<endl;
    printf("p4_greentropy: %.20Lf", p4_greentropy);
    cout<<endl;
    printf("p4_redtropy:   %.20Lf", p4_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 5: "<<endl;
    printf("p5_alltropy:   %.20Lf", p5_alltropy);
    cout<<endl;
    printf("p5_bluetropy:  %.20Lf", p5_bluetropy);
    cout<<endl;
    printf("p5_greentropy: %.20Lf", p5_greentropy);
    cout<<endl;
    printf("p5_redtropy:   %.20Lf", p5_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 6: "<<endl;
    printf("p6_alltropy:   %.20Lf", p6_alltropy);
    cout<<endl;
    printf("p6_bluetropy:  %.20Lf", p6_bluetropy);
    cout<<endl;
    printf("p6_greentropy: %.20Lf", p6_greentropy);
    cout<<endl;
    printf("p6_redtropy:   %.20Lf", p6_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 7: "<<endl;
    printf("p7_alltropy:   %.20Lf", p7_alltropy);
    cout<<endl;
    printf("p7_bluetropy:  %.20Lf", p7_bluetropy);
    cout<<endl;
    printf("p7_greentropy: %.20Lf", p7_greentropy);
    cout<<endl;
    printf("p7_redtropy:   %.20Lf", p7_redtropy);
    cout<<endl;

    cout<<"\nwyniki dla predykatora 8: "<<endl;
    printf("p8_alltropy:   %.20Lf", p8_alltropy);
    cout<<endl;
    printf("p8_bluetropy:  %.20Lf", p8_bluetropy);
    cout<<endl;
    printf("p8_greentropy: %.20Lf", p8_greentropy);
    cout<<endl;
    printf("p8_redtropy:   %.20Lf", p8_redtropy);
    cout<<endl<<"--------------------------------------------------";
    cout<<endl;

    cout<<"Optymalne kodowania dla poszczegolnych kolorów: "<<endl;

    cout<<endl<<"Dla całego pliku:"<<endl;
    best_predyktor(alltropy, p1_alltropy, p2_alltropy, p3_alltropy, p4_alltropy, p5_alltropy, p6_alltropy, p7_alltropy, p8_alltropy);

    cout<<"Dla koloru niebieskiego:"<<endl;
    best_predyktor(bluetropy, p1_bluetropy, p2_bluetropy, p3_bluetropy, p4_bluetropy, p5_bluetropy, p6_bluetropy, p7_bluetropy, p8_bluetropy);

    cout<<"Dla koloru zielonego:"<<endl;
    best_predyktor(greentropy, p1_greentropy, p2_greentropy, p3_greentropy, p4_greentropy, p5_greentropy, p6_greentropy, p7_greentropy, p8_greentropy);

    cout<<"Dla koloru czerwonego: "<<endl;
    best_predyktor(redtropy, p1_redtropy, p2_redtropy, p3_redtropy, p4_redtropy, p5_redtropy, p6_redtropy, p7_redtropy, p8_redtropy);


    return 0;

}