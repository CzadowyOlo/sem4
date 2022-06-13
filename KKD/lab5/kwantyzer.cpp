// TGA vector quantization

#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
#include <chrono>
#include <algorithm>
#include <time.h>

#include "kwantyzer.h"

using namespace std;

double modulo(double x){
    if(x < 0)
    {
        return 256 + x;
    }
    else if (x > 255 )
    {
        return x - 255;
    }
    else{
        return x;
    }
}
double maksimum(double a, double b, double c){
    double maks = 0;
    double tab[3] = {a, b, c};
    for(int i = 0; i < 3; i++){
        if(tab[i] >= maks) maks = tab[i];
    }

    return maks;
}

double metryka_euklides_wagi(struct pixel pixel, struct coloroids centroid)
{
    return pow((pow((2*((double)pixel.r - centroid.r)),2) + 
           pow((4*((double)pixel.g - centroid.g)),2) + 
           pow((((double)pixel.b - centroid.b)),2)), 0.34);
}

double metryka_taxi(struct pixel pixel, struct coloroids centroid)
{
    return ((((2*abs((double)pixel.r - centroid.r))) + 
           ((4*abs((double)pixel.g - centroid.g))) + 
           ((abs((double)pixel.b - centroid.b)))));
}

long double metryka_centrum(struct pixel pixel, struct coloroids centroid)
{
    return ((pow((pow((((long double)pixel.r - 127.5)),2) + 
           pow((((long double)pixel.g - 127.5)),2) + 
           pow((((long double)pixel.b - 127.5)),2)), 0.34)) +
           (pow((pow(((127.5 - centroid.r)),2) + 
           pow(((127.5 - centroid.g)),2) + 
           pow(((127.5 - centroid.b)),2)), 0.34))/2) +
           (pow((pow((((long double)pixel.r - centroid.r)),2) + 
           pow((((long double)pixel.g - centroid.g)),2) + 
           pow((((long double)pixel.b - centroid.b)),2)), 0.34));
}

double metryka_czebyszewa(struct pixel pixel, struct coloroids centroid){
    return maksimum(((double)pixel.r - centroid.r), ((double)pixel.g - centroid.g), ((double)pixel.b - centroid.b));
}

double avg_disorder(struct pixel image[], int pixels, struct coloroids centroid){

    double sum = 0;

    for(int i = 0; i < pixels; i++){
        sum += metryka_taxi(image[i], centroid);
    }

    return sum / (double) pixels;
}



void getHeader(FILE* f, FILE* myfile, header *header){
    
    char sym;
    if(f){
        cout<<"dupa"<<endl;

        header->F1 = getchar();
        header->F2 = getchar();
        header->F3 = getchar();
        header->F4_1 = getchar() + 256*getchar();
        header->F4_2 = getchar() + 256*getchar();
        header->F4_3 = getchar();
        header->F5_1 = getchar() + 256*getchar();
        header->F5_2 = getchar() + 256*getchar();
        header->F5_3 = getchar() + 256*getchar();
        header->F5_4 = getchar() + 256*getchar();
        header->F5_5 = getchar();
        header->F5_6 = getchar();
        header->order = (header->F5_6) & (header->help_operator);

        fwrite(&(header->F1), 1, 1, myfile);
        fwrite(&(header->F2), 1, 1, myfile);
        fwrite(&(header->F3), 1, 1, myfile);
        fwrite(&(header->F4_1), 2, 1, myfile);
        fwrite(&(header->F4_2), 2, 1, myfile);
        fwrite(&(header->F4_3), 1, 1, myfile);
        fwrite(&(header->F5_1), 2, 1, myfile);
        fwrite(&(header->F5_2), 2, 1, myfile);
        fwrite(&(header->F5_3), 2, 1, myfile);
        fwrite(&(header->F5_4), 2, 1, myfile);
        fwrite(&(header->F5_5), 1, 1, myfile);
        fwrite(&(header->F5_6), 1, 1, myfile);

        for(int i = 0; i < (int)(header->F2) + ((int)(header->F4_2) * (int)(header->F4_3)); i++){
            sym = getchar();
            fwrite(&sym, 1, 1, myfile);
        }

        cout<<"F1  : "<<header->F1<<endl;
        cout<<"F2  : "<<header->F2<<endl;
        cout<<"F3  : "<<header->F3<<endl;
        cout<<"F4_1: "<<header->F4_1<<endl;
        cout<<"F4_2: "<<header->F4_2<<endl;
        cout<<"F4_3: "<<header->F4_3<<endl;
        cout<<"F5_1 - X spawn     : "<<header->F5_1<<endl;
        cout<<"F5_2 - Y spawn     : "<<header->F5_2<<endl;
        cout<<"F5_3 - image width : "<<header->F5_3<<endl;
        cout<<"F5_4 - image height: "<<header->F5_4<<endl;
        cout<<"F5_5 - pixel depth : "<<header->F5_5<<endl;
        cout<<"F5_6 - descriptor  : "<<header->F5_6<<endl;
        cout<<"order: ";
        switch(header->order){
            case 0:
                cout<<header->order<<" (left-bottom)"<<endl;
                break;
            case 16:
                cout<<header->order<<" (right-bottom)"<<endl;
                break;
            case 32:
                cout<<header->order<<" (left-top)"<<endl;  
                break;
            case 48:
                cout<<header->order<<" (right-top)"<<endl;      
                break;
            default:
                cout<<header->order<<" fault"<<endl;
                break;    
            

        }
    }
}

void get_footer(FILE* f, FILE* myfile)
{
    char sym;
    while ((sym = getchar()) != EOF)
    {
        fwrite(&sym, 1, 1, myfile);
    }
}

void add(int *a){
    *a = *a + 1;
    //return a;
}


void averaging_of_centroids(struct coloroids coloroids_help[], size_t colors_counter, struct pixel image[], int pixels ){

    double min_distance = 6969;
    double current_distance = 6969;
    size_t coloroids_indeks = 0;

    for(size_t i = 0; i < colors_counter; i++){
        coloroids_help[i].pixel_tab_size = 0;
        coloroids_help[coloroids_indeks].b_pixel = 0.0;
        coloroids_help[coloroids_indeks].g_pixel = 0.0;
        coloroids_help[coloroids_indeks].r_pixel = 0.0;

    }
    for(int i = 0; i < pixels; i++){ // petla po pikselach
    //cout<<"przejscie po pikselach nr: "<<i<<endl;

        for(size_t j = 0; j < colors_counter; j++){ // petlla po centroidach

        //cout<<"przejscie po coloroidach nr: "<<j<<endl;
            current_distance = metryka_euklides_wagi(image[i], coloroids_help[j]);
            if(current_distance <= min_distance){
                //cout<<"curr dist: "<<current_distance<<"for j: "<<j<<endl;
                min_distance = current_distance;
                coloroids_indeks = j;
            }
            image[i].index_centroida = coloroids_indeks;
            
        }
        min_distance = 6969;

        //znaleźliśmy dla danego piksela jego najbliższy centroid
        

        coloroids_help[coloroids_indeks].b_pixel += image[i].b;
        coloroids_help[coloroids_indeks].g_pixel += image[i].g;
        coloroids_help[coloroids_indeks].r_pixel += image[i].r;
        coloroids_help[coloroids_indeks].pixel_tab_size++;
        //cout<<(int)image[i].b<<endl;

    }

    size_t max_size = 0;
    size_t max_index = 0;

    for(size_t j = 0; j < colors_counter; j++){
        //cout<<"i am here on j = "<<j<<endl;
        coloroids_help[j].b = coloroids_help[j].b_pixel / (double)coloroids_help[j].pixel_tab_size;
        coloroids_help[j].g = coloroids_help[j].g_pixel / (double)coloroids_help[j].pixel_tab_size;
        coloroids_help[j].r = coloroids_help[j].r_pixel / (double)coloroids_help[j].pixel_tab_size;

        if (coloroids_help[j].pixel_tab_size > max_size)
        {
            max_index = j;
            max_size = coloroids_help[j].pixel_tab_size;
        }



        cout<< "centroid nr: "<<j<<", colors: B: "<<coloroids_help[j].b <<", G: "<<coloroids_help[j].g <<", R: "<<coloroids_help[j].r << endl;
    }    

    // for (size_t j = 0; j < colors_counter; j++)
    // {
    //     if(coloroids_help[j].pixel_tab_size == 0)
    //     {
    //         srand(time(NULL));
    //         size_t r_ind = rand() % max_size;
    //         coloroids_help[j].r = coloroids_help[max_index].pixel_tab.at(r_ind).r;
    //         coloroids_help[j].g = coloroids_help[max_index].pixel_tab.at(r_ind).g;
    //         coloroids_help[j].b = coloroids_help[max_index].pixel_tab.at(r_ind).b;
    //     }
    // }

}


int main(int argc, char **argv){

    FILE *f = freopen(argv[1], "rb", stdin);  // input
    FILE *myfile = fopen(argv[2], "wb");

    size_t colors_count = pow(2, stoi(argv[3]));
    cout<<"ilosc colorow: "<<colors_count<<endl;

    struct header header;
    getHeader(f, myfile, &header);

    int pixels = header.F5_3 * header.F5_4;
    cout<<"pixels: "<<pixels<<endl;

    struct pixel image[pixels];

    double div = (double) pixels; // do sredniego pixela
    size_t sum_b = 0;
    size_t sum_g = 0;
    size_t sum_r = 0;

    uint8_t blue, green, red;

    for(int i = 0; i < pixels; i++){
        blue = getchar();
        green = getchar();
        red = getchar();

        image[i] = {.b = blue, .g = green, .r = red};
        //cout<<image[i].b<<", "<<image[i].g<<", "<<image[i].r<<", ";

        sum_b += (size_t)blue;
        sum_g += (size_t)green;
        sum_r += (size_t)red;

    } 
    //cout<<"git"<<endl;
    
    struct coloroids centroid = {.b = sum_b/div, .g = sum_g/div, .r = sum_r/div,}; // pierwszy centroid ze sredniej

    cout<<"initial state avg centroid colors:"<<endl;
    cout<<(double)centroid.b<<endl;
    cout<<(double)centroid.g<<endl;
    cout<<(double)centroid.r<<endl;
    cout<<endl;

    double disorder = avg_disorder(image, pixels, centroid);

    cout<<"avg disorder: "<<disorder<<endl;
    cout<<"-------------------------"<<endl;

    struct coloroids centroids[colors_count]; // wpisaliśmy centroida (avg)
    

    struct coloroids centroids_help[colors_count]; // kopia tego wyżej

    centroids_help[0] = {.b = centroid.b, .g = centroid.g, .r = centroid.r};

    
    //splitting------------------------------------------------------
    size_t colors_counter = 1;
    double epsylon = 0.00001;

    double epsylons[4] = {-0.3, 0.82, 0.0, 0.076};
    double e_r;
    double e_g;
    double e_b;

    double epsylons_n[4] = {-0.7, 0.00623, 0.01, 0.02};
    double e_r_n;
    double e_g_n;
    double e_b_n;

    while(colors_counter < colors_count){
        cout<<"splitting..."<<endl;
        srand(time(NULL));

        e_r = epsylons[rand()%4];
        e_g = epsylons[rand()%4];
        e_b = epsylons[rand()%4];

        e_r_n = epsylons_n[rand()%4];
        e_g_n = epsylons_n[rand()%4];
        e_b_n = epsylons_n[rand()%4];

        for(size_t i = 0; i < colors_counter; i++){
            centroids[2*i] = {.b = centroids_help[i].b - epsylon + e_b, .g = centroids_help[i].g - epsylon + e_g, .r = centroids_help[i].r - epsylon + e_r };


            centroids[2*i + 1] = {.b = centroids_help[i].b + epsylon  + e_b_n, .g = centroids_help[i].g + epsylon + e_g_n, .r = centroids_help[i].r + epsylon + e_r_n };


        }

        for(size_t i = 0; i < colors_counter; i++){

            centroids_help[2*i] = {.b = centroids[2*i].b, .g = centroids[2*i].g, .r = centroids[2*i].r };

            centroids_help[2*i + 1] = {.b = centroids[2*i +1].b, .g = centroids[2*i + 1].g, .r = centroids[2*i + 1].r};
        }    

        colors_counter = colors_counter * 2;

        // wywolujemy funkcje, która zmieni nam centroidy na średnie ich pikseli || mamy dwa centroidy, każdy z nich dostanie 
        // kilkaset pikseli, które są najbliższe tym centroidom
        // teraz dla każdego centroida z tablicy liczymy średnią po pikselach z ich vectora
        // nadpisujemy centroidy z naszej tablicy wyliczonymi odpowiednio średnimi

        //cout<<"before: "<<endl;
        cout<<"colors counter: "<<colors_counter<<endl;
        cout<<"searching for new averages...."<<endl;
        averaging_of_centroids(centroids_help, colors_counter, image, pixels);
        //cout<<"after: "<<endl;

        // long double e = 0.0;
        // for (size_t j = 0; j < colors_counter; j++)
        // {
        //     for (size_t i = 0; i < centroids_help[j].pixel_tab_size; i++)
        //     {
        //      e+=metryka_euklides_wagi(centroids_help[j].pixel_tab.at(i),centroids_help[j]);
        //     }
        // }
        // if(1+epsylon > e/(double)pixels)
        //     break;

        
    }

    for(size_t i = 0; i < colors_count; i++){
        cout<<"ile pikseli w koloroidzie nr: "<<i<<" = "<<centroids_help[i].pixel_tab_size<<endl;
    }

    uint8_t color_b;
    uint8_t color_g;
    uint8_t color_r;

    for(int i = 0; i < pixels; i++){

    
        color_b = (char) (floor((centroids_help[image[i].index_centroida].b)));
        color_g = (char) (floor((centroids_help[image[i].index_centroida].g)));
        color_r = (char) (floor((centroids_help[image[i].index_centroida].r)));
        
        fwrite(&color_b, 1, 1, myfile);
        fwrite(&color_g, 1, 1, myfile);
        fwrite(&color_r, 1, 1, myfile);
    }


    get_footer(f, myfile);
    fclose(f);
    fclose(myfile);
    return 0;
}
