#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <tgmath.h>
#include <time.h>
#include "hujozer.h"


double modulo(double row){
    if(row < 0)
    {
        return 256 + row;
    }
    else if (row > 255 )
    {
        return row - 255;
    }
    else{
        return row;
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

void make_kwantyzator_r(size_t n, char kwant[]) {
    char k = 256/n;
    kwant[(n/2)] = k/2;
    for (size_t i = (n/2)+1; i < n; i++) {
        kwant[i] = kwant[i-1]+k;
    }
    for (size_t i = 0; i < n/2; i++) {
        kwant[i] = -(kwant[n-1-i]);
    }
}

void jpeg_traverse(size_t row, size_t column, pixel map[row][column], d_pixel avg[row][column], d_pixel dev[row][column]){
    size_t i = 0;
    size_t j = 0;
    unsigned char temp_r;
    unsigned char temp_g;
    unsigned char temp_b;

    unsigned char prev_r;
    unsigned char prev_g;
    unsigned char prev_b;

    temp_b = map[i][j+1].B;
    temp_g = map[i][j+1].G;
    temp_r = map[i][j+1].R;

    prev_r = temp_r;
    prev_b = temp_b;
    prev_g = temp_g;

    avg[i][j].B = (double)map[i][j].B;
    avg[i][j].G = (double)map[i][j].G;
    avg[i][j].R = (double)map[i][j].R; 

    avg[i][j+1].B = ((double)map[i][j].B + (double)map[i][j+1].B)/2.0;
    avg[i][j+1].G = ((double)map[i][j].G + (double)map[i][j+1].G)/2.0;
    avg[i][j+1].R = ((double)map[i][j].R + (double)map[i][j+1].R)/2.0;

    dev[i][j].B = (double)map[i][j].B;
    dev[i][j].G = (double)map[i][j].G;
    dev[i][j].R = (double)map[i][j].R; 
    dev[i][j+1].B = ((double)map[i][j].B - (double)map[i][j+1].B)/2.0;
    dev[i][j+1].G = ((double)map[i][j].G - (double)map[i][j+1].G)/2.0;
    dev[i][j+1].R = ((double)map[i][j].R - (double)map[i][j+1].R)/2.0;

    j++;
    int counter = 0;
    while(! (i == row-1 && j == column-1)){
        printf("counter: %d ,  i = %zu, j= %zu \n", counter, i, j);
        counter++;
        while(j > 0 && i+1 < row){ //left down
            temp_b = map[i+1][j-1].B;
            temp_g = map[i+1][j-1].G;
            temp_r = map[i+1][j-1].R;


            avg[i+1][j-1].B = (((double)prev_b + (double)map[i+1][j-1].B)/2.0);
            avg[i+1][j-1].G = (((double)prev_g + (double)map[i+1][j-1].G)/2.0);
            avg[i+1][j-1].R = (((double)prev_r + (double)map[i+1][j-1].R)/2.0);

            dev[i+1][j-1].B = (((double)prev_b - (double)map[i+1][j-1].B)/2.0);
            dev[i+1][j-1].G = (((double)prev_g - (double)map[i+1][j-1].G)/2.0);
            dev[i+1][j-1].R = (((double)prev_r - (double)map[i+1][j-1].R)/2.0);

            prev_r = temp_r;
            prev_b = temp_b;
            prev_g = temp_g;

            i++;
            j--;
        }

        if( i+1 < row ){ //down

            temp_b = map[i+1][j].B;
            temp_g = map[i+1][j].G;
            temp_r = map[i+1][j].R;

            avg[i+1][j].B = (((double)prev_b + (double)map[i+1][j].B)/2.0);
            avg[i+1][j].G = (((double)prev_g + (double)map[i+1][j].G)/2.0);
            avg[i+1][j].R = (((double)prev_r + (double)map[i+1][j].R)/2.0);

            dev[i+1][j].B = (((double)prev_b - (double)map[i+1][j].B)/2.0);
            dev[i+1][j].G = (((double)prev_g - (double)map[i+1][j].G)/2.0);
            dev[i+1][j].R = (((double)prev_r - (double)map[i+1][j].R)/2.0);

            prev_r = temp_r;
            prev_b = temp_b;
            prev_g = temp_g;

            i++;
        }
        else{ //right
            temp_b = map[i][j+1].B;
            temp_g = map[i][j+1].G;
            temp_r = map[i][j+1].R;

            avg[i][j+1].B = (((double)prev_b + (double)map[i][j+1].B)/2.0);
            avg[i][j+1].G = (((double)prev_g + (double)map[i][j+1].G)/2.0);
            avg[i][j+1].R = (((double)prev_r + (double)map[i][j+1].R)/2.0);

            dev[i][j+1].B = (((double)prev_b - (double)map[i][j+1].B)/2.0);
            dev[i][j+1].G = (((double)prev_g - (double)map[i][j+1].G)/2.0);
            dev[i][j+1].R = (((double)prev_r - (double)map[i][j+1].R)/2.0);

            prev_r = temp_r;
            prev_b = temp_b;
            prev_g = temp_g;

            j++;
        }
        if(i + 1 >= row && j + 1 >= column){
            printf("\n \n SRAAAAAAAAAAAAANNIE\n \n");
            printf("i = %zu and j = %zu \n", i, j);
            break;
        }
        while (i > 0 && j+1 < column){ //right up

            temp_b = map[i-1][j+1].B;
            temp_g = map[i-1][j+1].G;
            temp_r = map[i-1][j+1].R;

            avg[i-1][j+1].B = (((double)prev_b + (double)map[i-1][j+1].B)/2.0);
            avg[i-1][j+1].G = (((double)prev_g + (double)map[i-1][j+1].G)/2.0);
            avg[i-1][j+1].R = (((double)prev_r + (double)map[i-1][j+1].R)/2.0);

            dev[i-1][j+1].B = (((double)prev_b - (double)map[i-1][j+1].B)/2.0);
            dev[i-1][j+1].G = (((double)prev_g - (double)map[i-1][j+1].G)/2.0);
            dev[i-1][j+1].R = (((double)prev_r - (double)map[i-1][j+1].R)/2.0);

            prev_r = temp_r;
            prev_b = temp_b;
            prev_g = temp_g;

            i--;
            j++;
        }
        if(j+1 < column){ // right

            temp_b = map[i][j+1].B;
            temp_g = map[i][j+1].G;
            temp_r = map[i][j+1].R;

            avg[i][j+1].B = (((double)prev_b + (double)map[i][j+1].B)/2.0);
            avg[i][j+1].G = (((double)prev_g + (double)map[i][j+1].G)/2.0);
            avg[i][j+1].R = (((double)prev_r + (double)map[i][j+1].R)/2.0);

            dev[i][j+1].B = (((double)prev_b - (double)map[i][j+1].B)/2.0);
            dev[i][j+1].G = (((double)prev_g - (double)map[i][j+1].G)/2.0);
            dev[i][j+1].R = (((double)prev_r - (double)map[i][j+1].R)/2.0);

            prev_r = temp_r;
            prev_b = temp_b;
            prev_g = temp_g;

            j++;
        }
        else{ // down
            temp_b = map[i+1][j].B;
            temp_g = map[i+1][j].G;
            temp_r = map[i+1][j].R;

            avg[i+1][j].B = (((double)prev_b + (double)map[i+1][j].B)/2.0);
            avg[i+1][j].G = (((double)prev_g + (double)map[i+1][j].G)/2.0);
            avg[i+1][j].R = (((double)prev_r + (double)map[i+1][j].R)/2.0);

            dev[i+1][j].B = (((double)prev_b - (double)map[i+1][j].B)/2.0);
            dev[i+1][j].G = (((double)prev_g - (double)map[i+1][j].G)/2.0);
            dev[i+1][j].R = (((double)prev_r - (double)map[i+1][j].R)/2.0);

            prev_r = temp_r;
            prev_b = temp_b;
            prev_g = temp_g;

            i++;
        }

    }

}

char kwantthis(double color, size_t kwant_count, char kwantyzator[kwant_count]){
    double minimum = 6969.69;
    double min = 8888;
    size_t current;
    for (size_t i = 0; i < kwant_count; i++){
        min = fabs(color - kwantyzator[i]);
        if(min <= minimum){
            minimum = min;
            current = i;
        }
    }
    return kwantyzator[current];
}

void DPCM_JPEG2 (size_t row, size_t column, size_t kwant_count, d_pixel dev[row][column], char kwantyzator[kwant_count], c_pixel kwanted_diffs[row][column], pixel rekonstructed[row][column]){
    // pixel rekonstructed[row][column];

    size_t i = 0;
    size_t j = 0;

    d_pixel differs[row][column];

    rekonstructed[0][0].B = (uint8_t)kwantthis(dev[0][0].B, kwant_count, kwantyzator);
    rekonstructed[0][0].G = (uint8_t)kwantthis(dev[0][0].G, kwant_count, kwantyzator);
    rekonstructed[0][0].R = (uint8_t)kwantthis(dev[0][0].R, kwant_count, kwantyzator);
    differs[0][0].B = dev[0][0].B;
    differs[0][0].G = dev[0][0].G;
    differs[0][0].R = dev[0][0].R;
    kwanted_diffs[0][0].B = kwantthis(dev[0][0].B, kwant_count, kwantyzator);
    kwanted_diffs[0][0].G = kwantthis(dev[0][0].G, kwant_count, kwantyzator);
    kwanted_diffs[0][0].R = kwantthis(dev[0][0].R, kwant_count, kwantyzator);

    differs[0][1].B = dev[0][1].B - rekonstructed[0][0].B;
    differs[0][1].G = dev[0][1].G - rekonstructed[0][0].G;
    differs[0][1].R = dev[0][1].R - rekonstructed[0][0].R;

    kwanted_diffs[0][1].B = kwantthis(dev[0][1].B, kwant_count, kwantyzator);
    kwanted_diffs[0][1].G = kwantthis(dev[0][1].G, kwant_count, kwantyzator);
    kwanted_diffs[0][1].R = kwantthis(dev[0][1].R, kwant_count, kwantyzator);

    rekonstructed[0][1].B = rekonstructed[0][0].B - (uint8_t)abs(kwanted_diffs[0][1].B);
    rekonstructed[0][1].G = rekonstructed[0][0].G - (uint8_t)abs(kwanted_diffs[0][1].G);
    rekonstructed[0][1].R = rekonstructed[0][0].R - (uint8_t)abs(kwanted_diffs[0][1].R);


    while (!(i == (row-1) && j == (column-1)))
    {
        if (j < column-1 && (i == 0 || i == row-1)) { // idziemy w praw

            differs[i][j+1].B = dev[i][j+1].B - rekonstructed[i][j].B;
            kwanted_diffs[i][j+1].B = kwantthis(differs[i][j+1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].B < 0){
                rekonstructed[i][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i][j+1].B);
            }
            else{
                rekonstructed[i][j+1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i][j+1].B;
            }

            differs[i][j+1].G = dev[i][j+1].G - rekonstructed[i][j].G;
            kwanted_diffs[i][j+1].G = kwantthis(differs[i][j+1].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].G < 0){
                rekonstructed[i][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i][j+1].G);
            }
            else{
                rekonstructed[i][j+1].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i][j+1].G;
            }

            differs[i][j+1].R = dev[i][j+1].R - rekonstructed[i][j].R;
            kwanted_diffs[i][j+1].R = kwantthis(differs[i][j+1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].R < 0){
                rekonstructed[i][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i][j+1].R);
            }
            else{
                rekonstructed[i][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i][j+1].R;
            }        
            ++j;
        //fill_avg_dev(row,column,avg,dev,i,j,pixel[i][j],pixel[i][j-1]);
        }
        while (j > 0 && i < row-1) { // Idziemy na lewo w dół /
            differs[i+1][j-1].B = dev[i+1][j-1].B - rekonstructed[i][j].B;
            kwanted_diffs[i+1][j-1].B = kwantthis(differs[i+1][j-1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j-1].B < 0){
                rekonstructed[i+1][j-1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][j-1].B);
            }
            else{
                rekonstructed[i+1][j-1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][j-1].B;
            }

            differs[i+1][j-1].G = dev[i+1][j-1].G - rekonstructed[i][j].G;
            kwanted_diffs[i+1][j-1].G = kwantthis(differs[i+1][j-1].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j-1].G < 0){
                rekonstructed[i+1][j-1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][j-1].G);
            }
            else{
                rekonstructed[i+1][j-1].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][j-1].G;
            }

            differs[i+1][j-1].R = dev[i+1][j-1].R - rekonstructed[i][j].R;
            kwanted_diffs[i+1][j-1].R = kwantthis(differs[i+1][j-1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j-1].R < 0){
                rekonstructed[i+1][j-1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][j-1].R);
            }
            else{
                rekonstructed[i+1][j-1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][j-1].R;
            }

            --j;
            ++i;
            //fill_avg_dev(row,column,avg,dev,i,j,pixel[i][j],pixel[i-1][j+1]);
        }
        if (i == row-1 && j < column-1) { // idziemy w prawo */
            differs[i][j+1].B = dev[i][j+1].B - rekonstructed[i][j].B;
            kwanted_diffs[i][j+1].B = kwantthis(differs[i][j+1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].B < 0){
                rekonstructed[i][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i][j+1].B);
            }
            else{
                rekonstructed[i][j+1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i][j+1].B;
            }

            differs[i][j+1].G = dev[i][j+1].G - rekonstructed[i][j].G;

            printf("\n\n\n diff[%zu][%zu]: %lf \n \n \n", i, j, differs[i][j+1].G);
            
            kwanted_diffs[i][j+1].G = kwantthis(differs[i][j+1].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].G < 0){
                rekonstructed[i][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i][j+1].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i][j+1].G;
            }

            differs[i][j+1].R = dev[i][j+1].R - rekonstructed[i][j].R;
            kwanted_diffs[i][j+1].R = kwantthis(differs[i][j+1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].R < 0){
                rekonstructed[i][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i][j+1].R);
            }
            else{
                rekonstructed[i][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i][j+1].R;
            }

            ++j;
            //fill_avg_dev(row,column,avg,dev,i,j,pixel[i][j],pixel[i][j-1]); 
        }
        if (i < row-1 && (j == 0 || j == column-1)) { // jeśli nie jesteśmy dolnej krawedzi idziemy w dół 

            differs[i+1][j].B = dev[i+1][j].B - rekonstructed[i][j].B;
            kwanted_diffs[i+1][j].B = kwantthis(differs[i+1][j].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].B < 0){
                rekonstructed[i+1][j].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][j].B);
            }
            else{
                rekonstructed[i+1][j].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][j].B;
            }

            differs[i+1][j].G = dev[i+1][j].G - rekonstructed[i][j].G;
            kwanted_diffs[i+1][j].G = kwantthis(differs[i+1][j].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].G < 0){
                rekonstructed[i+1][j].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][j].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][j].G;
            }

            differs[i+1][j].R = dev[i+1][j].R - rekonstructed[i][j].R;
            kwanted_diffs[i+1][j].R = kwantthis(differs[i+1][j].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].R < 0){
                rekonstructed[i+1][j].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][j].R);
            }
            else{
                rekonstructed[i+1][j].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][j].R;
            }        
            ++i;
            //fill_avg_dev(row,column,avg,dev,i,j,pixel[i][j],pixel[i-1][j]); 
        } 
        while (i > 0 && j < column-1) {
            differs[i-1][j+1].B = dev[i-1][j+1].B - rekonstructed[i][j].B;
            kwanted_diffs[i-1][j+1].B = kwantthis(differs[i-1][j+1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i-1][j+1].B < 0){
                rekonstructed[i-1][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i-1][j+1].B);
            }
            else{
                rekonstructed[i-1][j+1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i-1][j+1].B;
            }

            differs[i-1][j+1].G = dev[i-1][j+1].G - rekonstructed[i][j].G;
            kwanted_diffs[i-1][j+1].G = kwantthis(differs[i-1][j+1].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i-1][j+1].G < 0){
                rekonstructed[i-1][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i-1][j+1].G);
            }
            else{
                rekonstructed[i-1][j+1].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i-1][j+1].G;
            }

            differs[i-1][j+1].R = dev[i-1][j+1].R - rekonstructed[i][j].R;
            kwanted_diffs[i-1][j+1].R = kwantthis(differs[i-1][j+1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i-1][j+1].R < 0){
                rekonstructed[i-1][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i-1][j+1].R);
            }
            else{
                rekonstructed[i-1][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i-1][j+1].R;
            }            
            ++j;
            --i;
            //fill_avg_dev(row,column,avg,dev,i,j,pixel[i][j],pixel[i+1][j-1]); 
        }
        if (j == column-1 && i < row-1) {
            differs[i+1][j].B = dev[i+1][j].B - rekonstructed[i][j].B;
            kwanted_diffs[i+1][j].B = kwantthis(differs[i+1][j].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].B < 0){
                rekonstructed[i+1][j].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][j].B);
            }
            else{
                rekonstructed[i+1][j].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][j].B;
            }

            differs[i+1][j].G = dev[i+1][j].G - rekonstructed[i][j].G;
            kwanted_diffs[i+1][j].G = kwantthis(differs[i+1][j].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].G < 0){
                rekonstructed[i+1][j].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][j].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][j].G;
            }

            differs[i+1][j].R = dev[i+1][j].R - rekonstructed[i][j].R;
            kwanted_diffs[i+1][j].R = kwantthis(differs[i+1][j].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].R < 0){
                rekonstructed[i+1][j].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][j].R);
            }
            else{
                rekonstructed[i+1][j].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][j].R;
            }
            ++i;
            //fill_avg_dev(row,column,avg,dev,i,j,pixel[i][j],pixel[i-1][j]); 
        }
    }

    //uint8_t prev_b = rekonstructed[0][1];
    
    
}

void DPCM_JPEG (size_t row, size_t column, size_t kwant_count, d_pixel dev[row][column], char kwantyzator[kwant_count], c_pixel kwanted_diffs[row][column], pixel rekonstructed[row][column]){
    // pixel rekonstructed[row][column];

    size_t i = 0;
    size_t j = 0;

    d_pixel differs[row][column];

    rekonstructed[0][0].B = (uint8_t)kwantthis(dev[0][0].B, kwant_count, kwantyzator);
    rekonstructed[0][0].G = (uint8_t)kwantthis(dev[0][0].G, kwant_count, kwantyzator);
    rekonstructed[0][0].R = (uint8_t)kwantthis(dev[0][0].R, kwant_count, kwantyzator);
    differs[0][0].B = dev[0][0].B;
    differs[0][0].G = dev[0][0].G;
    differs[0][0].R = dev[0][0].R;
    kwanted_diffs[0][0].B = kwantthis(dev[0][0].B, kwant_count, kwantyzator);
    kwanted_diffs[0][0].G = kwantthis(dev[0][0].G, kwant_count, kwantyzator);
    kwanted_diffs[0][0].R = kwantthis(dev[0][0].R, kwant_count, kwantyzator);

    differs[0][1].B = dev[0][1].B - rekonstructed[0][0].B;
    differs[0][1].G = dev[0][1].G - rekonstructed[0][0].G;
    differs[0][1].R = dev[0][1].R - rekonstructed[0][0].R;

    kwanted_diffs[0][1].B = kwantthis(dev[0][1].B, kwant_count, kwantyzator);
    kwanted_diffs[0][1].G = kwantthis(dev[0][1].G, kwant_count, kwantyzator);
    kwanted_diffs[0][1].R = kwantthis(dev[0][1].R, kwant_count, kwantyzator);

    rekonstructed[0][1].B = rekonstructed[0][0].B - (uint8_t)abs(kwanted_diffs[0][1].B);
    rekonstructed[0][1].G = rekonstructed[0][0].G - (uint8_t)abs(kwanted_diffs[0][1].G);
    rekonstructed[0][1].R = rekonstructed[0][0].R - (uint8_t)abs(kwanted_diffs[0][1].R);

    //uint8_t prev_b = rekonstructed[0][1];
    
    j++;
    int counter = 0;
    while(! (i == row-1 && j == column-1)){
        printf("counter: %d ,  i = %zu, j= %zu \n", counter, i, j);
        counter++;
        while(j-1 > 0 && i+2 < row){ //left down

                differs[i+1][j-1].B = dev[i+1][j-1].B - rekonstructed[i][j].B;
                kwanted_diffs[i+1][j-1].B = kwantthis(differs[i+1][j-1].B, kwant_count, kwantyzator);

                if(kwanted_diffs[i+1][j-1].B < 0){
                    rekonstructed[i+1][j-1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][j-1].B);
                }
                else{
                    rekonstructed[i+1][j-1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][j-1].B;
                }

                differs[i+1][j-1].G = dev[i+1][j-1].G - rekonstructed[i][j].G;
                kwanted_diffs[i+1][j-1].G = kwantthis(differs[i+1][j-1].G, kwant_count, kwantyzator);

                if(kwanted_diffs[i+1][j-1].G < 0){
                    rekonstructed[i+1][j-1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][j-1].G);
                }
                else{
                    rekonstructed[i+1][j-1].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][j-1].G;
                }

                differs[i+1][j-1].R = dev[i+1][j-1].R - rekonstructed[i][j].R;
                kwanted_diffs[i+1][j-1].R = kwantthis(differs[i+1][j-1].R, kwant_count, kwantyzator);

                if(kwanted_diffs[i+1][j-1].R < 0){
                    rekonstructed[i+1][j-1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][j-1].R);
                }
                else{
                    rekonstructed[i+1][j-1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][j-1].R;
                }

            i++;
            j--;
        }

        if( i+2 < row ){ //down

            differs[i+1][j].B = dev[i+1][j].B - rekonstructed[i][j].B;
            kwanted_diffs[i+1][j].B = kwantthis(differs[i+1][j].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].B < 0){
                rekonstructed[i+1][j].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][j].B);
            }
            else{
                rekonstructed[i+1][j].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][j].B;
            }

            differs[i+1][j].G = dev[i+1][j].G - rekonstructed[i][j].G;
            kwanted_diffs[i+1][j].G = kwantthis(differs[i+1][j].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].G < 0){
                rekonstructed[i+1][j].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][j].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][j].G;
            }

            differs[i+1][j].R = dev[i+1][j].R - rekonstructed[i][j].R;
            kwanted_diffs[i+1][j].R = kwantthis(differs[i+1][j].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].R < 0){
                rekonstructed[i+1][j].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][j].R);
            }
            else{
                rekonstructed[i+1][j].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][j].R;
            }

            i++;
        }
        else{ //right
            differs[i][j+1].B = dev[i][j+1].B - rekonstructed[i][j].B;
            kwanted_diffs[i][j+1].B = kwantthis(differs[i][j+1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].B < 0){
                rekonstructed[i][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i][j+1].B);
            }
            else{
                rekonstructed[i+1][j].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i][j+1].B;
            }

            differs[i][j+1].G = dev[i][j+1].G - rekonstructed[i][j].G;
            kwanted_diffs[i][j+1].G = kwantthis(differs[i+1][j].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].G < 0){
                rekonstructed[i][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i][j+1].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i][j+1].G;
            }

            differs[i][j+1].R = dev[i][j+1].R - rekonstructed[i][j].R;
            kwanted_diffs[i][j+1].R = kwantthis(differs[i][j+1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].R < 0){
                rekonstructed[i][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i][j+1].R);
            }
            else{
                rekonstructed[i][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i][j+1].R;
            }
            j++;
        }
        if(i + 1 >= row && j + 1 >= column){
            printf("\n \n SRAAAAAAAAAAAAANNIE\n \n");
            printf("i = %zu and j = %zu \n", i, j);
            break;
        }
        while (i -1 > 0 && j+2 < column){ //right up

            differs[i-1][j+1].B = dev[i-1][j+1].B - rekonstructed[i][j].B;
            kwanted_diffs[i-1][j+1].B = kwantthis(differs[i-1][j+1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i-1][j+1].B < 0){
                rekonstructed[i-1][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i-1][j+1].B);
            }
            else{
                rekonstructed[i-1][j+1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i-1][j+1].B;
            }

            differs[i-1][j+1].G = dev[i-1][j+1].G - rekonstructed[i][j].G;
            kwanted_diffs[i-1][j+1].G = kwantthis(differs[i-1][j+1].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i-1][j+1].G < 0){
                rekonstructed[i-1][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i-1][j+1].G);
            }
            else{
                rekonstructed[i-1][j+1].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i-1][j+1].G;
            }

            differs[i-1][j+1].R = dev[i-1][j+1].R - rekonstructed[i][j].R;
            kwanted_diffs[i-1][j+1].R = kwantthis(differs[i-1][j+1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i-1][j+1].R < 0){
                rekonstructed[i-1][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i-1][j+1].R);
            }
            else{
                rekonstructed[i-1][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i-1][j+1].R;
            }

            i--;
            j++;
        }
        if(j+2 < column){ // right
            differs[i][j+1].B = dev[i][j+1].B - rekonstructed[i][j].B;
            kwanted_diffs[i][j+1].B = kwantthis(differs[i][j+1].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].B < 0){
                rekonstructed[i][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i][j+1].B);
            }
            else{
                rekonstructed[i+1][j].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i][j+1].B;
            }

            differs[i][j+1].G = dev[i][j+1].G - rekonstructed[i][j].G;
            kwanted_diffs[i][j+1].G = kwantthis(differs[i+1][j].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].G < 0){
                rekonstructed[i][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i][j+1].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i][j+1].G;
            }

            differs[i][j+1].R = dev[i][j+1].R - rekonstructed[i][j].R;
            kwanted_diffs[i][j+1].R = kwantthis(differs[i][j+1].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i][j+1].R < 0){
                rekonstructed[i][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i][j+1].R);
            }
            else{
                rekonstructed[i][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i][j+1].R;
            }
            j++;
        }
        else{ // down
            differs[i+1][j].B = dev[i+1][j].B - rekonstructed[i][j].B;
            kwanted_diffs[i+1][j].B = kwantthis(differs[i+1][j].B, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].B < 0){
                rekonstructed[i+1][j].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][j].B);
            }
            else{
                rekonstructed[i+1][j].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][j].B;
            }

            differs[i+1][j].G = dev[i+1][j].G - rekonstructed[i][j].G;
            kwanted_diffs[i+1][j].G = kwantthis(differs[i+1][j].G, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].G < 0){
                rekonstructed[i+1][j].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][j].G);
            }
            else{
                rekonstructed[i+1][j].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][j].G;
            }

            differs[i+1][j].R = dev[i+1][j].R - rekonstructed[i][j].R;
            kwanted_diffs[i+1][j].R = kwantthis(differs[i+1][j].R, kwant_count, kwantyzator);

            if(kwanted_diffs[i+1][j].R < 0){
                rekonstructed[i+1][j].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][j].R);
            }
            else{
                rekonstructed[i+1][j].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][j].R;
            }

            i++;
        }

    }
}

void DPCM (size_t row, size_t column, size_t kwant_count, d_pixel dev[row][column], char kwantyzator[kwant_count], c_pixel kwanted_diffs[row][column], pixel rekonstructed[row][column]){
    
    // pixel rekonstructed[row][column];
    d_pixel differs[row][column];

    rekonstructed[0][0].B = (uint8_t)kwantthis(dev[0][0].B, kwant_count, kwantyzator);
    rekonstructed[0][0].G = (uint8_t)kwantthis(dev[0][0].G, kwant_count, kwantyzator);
    rekonstructed[0][0].R = (uint8_t)kwantthis(dev[0][0].R, kwant_count, kwantyzator);
    differs[0][0].B = dev[0][0].B;
    differs[0][0].G = dev[0][0].G;
    differs[0][0].R = dev[0][0].R;
    kwanted_diffs[0][0].B = kwantthis(dev[0][0].B, kwant_count, kwantyzator);
    kwanted_diffs[0][0].G = kwantthis(dev[0][0].G, kwant_count, kwantyzator);
    kwanted_diffs[0][0].R = kwantthis(dev[0][0].R, kwant_count, kwantyzator);

    for (size_t i = 0; i < row; i++){
        for (size_t j = 0; j < column; j++){
            
            if(j+1<column){
                differs[i][j+1].B = dev[i][j+1].B - rekonstructed[i][j].B;
                kwanted_diffs[i][j+1].B = kwantthis(differs[i][j+1].B, kwant_count, kwantyzator);

                if(kwanted_diffs[i][j+1].B < 0){
                    rekonstructed[i][j+1].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i][j+1].B);
                }
                else{
                    rekonstructed[i][j+1].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i][j+1].B;
                }

                differs[i][j+1].G = dev[i][j+1].G - rekonstructed[i][j].G;
                kwanted_diffs[i][j+1].G = kwantthis(differs[i][j+1].G, kwant_count, kwantyzator);

                if(kwanted_diffs[i][j+1].G < 0){
                    rekonstructed[i][j+1].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i][j+1].G);
                }
                else{
                    rekonstructed[i][j+1].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i][j+1].G;
                }

                differs[i][j+1].R = dev[i][j+1].R - rekonstructed[i][j].R;
                kwanted_diffs[i][j+1].R = kwantthis(differs[i][j+1].R, kwant_count, kwantyzator);

                if(kwanted_diffs[i][j+1].R < 0){
                    rekonstructed[i][j+1].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i][j+1].R);
                }
                else{
                    rekonstructed[i][j+1].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i][j+1].R;
                }

            }
            else if(i+1<row){
                differs[i+1][0].B = dev[i+1][0].B - rekonstructed[i][j].B;
                printf("ciba");
                kwanted_diffs[i+1][0].B = kwantthis(differs[i+1][0].B, kwant_count, kwantyzator);
                if(kwanted_diffs[i+1][0].B < 0){
                    rekonstructed[i+1][0].B = rekonstructed[i][j].B - (uint8_t)abs(kwanted_diffs[i+1][0].B);
                }
                else{
                    rekonstructed[i+1][0].B = rekonstructed[i][j].B + (uint8_t)kwanted_diffs[i+1][0].B;
                }

                differs[i+1][0].G = dev[i+1][0].G - rekonstructed[i][j].G;
                kwanted_diffs[i+1][0].G = kwantthis(differs[i+1][0].G, kwant_count, kwantyzator);
                if(kwanted_diffs[i+1][0].G < 0){
                    rekonstructed[i+1][0].G = rekonstructed[i][j].G - (uint8_t)abs(kwanted_diffs[i+1][0].G);
                }
                else{
                    rekonstructed[i+1][0].G = rekonstructed[i][j].G + (uint8_t)kwanted_diffs[i+1][0].G;
                }

                differs[i+1][0].R = dev[i+1][0].R - rekonstructed[i][j].R;
                kwanted_diffs[i+1][0].R = kwantthis(differs[i+1][0].R, kwant_count, kwantyzator);
                if(kwanted_diffs[i+1][0].R < 0){
                    rekonstructed[i+1][0].R = rekonstructed[i][j].R - (uint8_t)abs(kwanted_diffs[i+1][0].R);
                }
                else{
                    rekonstructed[i+1][0].R = rekonstructed[i][j].R + (uint8_t)kwanted_diffs[i+1][0].R;
                }

            }
        }
    }        
}

void getHeader(FILE* f, FILE* myfile, header *header){
    
    char sym;
    if(f){
        printf("dupa\n");

        header->F1 = (uint8_t)getchar();
        header->F2 = (uint8_t)getchar();
        header->F3 = (uint8_t)getchar();
        header->F4_1 = (uint8_t)getchar() + 256*(uint16_t)getchar();
        header->F4_2 = (uint8_t)getchar() + 256*(uint16_t)getchar();
        header->F4_3 = (uint8_t)getchar();
        header->F5_1 = (uint8_t)getchar() + 256*(uint16_t)getchar();
        header->F5_2 = (uint8_t)getchar() + 256*(uint16_t)getchar();
        header->F5_3 = (uint8_t)getchar() + 256*(uint16_t)getchar();
        header->F5_4 = (uint8_t)getchar() + 256*(uint16_t)getchar();
        header->F5_5 = (uint8_t)getchar();
        header->F5_6 = (uint8_t)getchar();
        header->order = (header->F5_6) & 48;

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
            sym = (char)getchar();
            fwrite(&sym, 1, 1, myfile);
        }

        printf("F1  : %hhu \n",header->F1);
        printf("F2  : %hhu \n",header->F2);
        printf("F3  : %hhu \n",header->F3);
        printf("F4_1: %u \n",header->F4_1);
        printf("F4_2: %u \n",header->F4_2);
        printf("F4_3: %u \n",header->F4_3);
        printf("F5_1 - X spawn     : %u \n",header->F5_1);
        printf("F5_2 - Y spawn     : %u \n",header->F5_2);
        printf("F5_3 - image width : %u \n",header->F5_3);
        printf("F5_4 - image height: %u \n",header->F5_4);
        printf("F5_5 - pixel depth : %hhu \n",header->F5_5);
        printf("F5_6 - descriptor  : %hhu \n",header->F5_6);
        printf("order: ");
        switch(header->order){
            case 0:
                printf(" %hhu, (left-bottom)", header->order);
                break;
            case 16:
                printf(" %hhu, (right-bottom)", header->order);
                break;
            case 32:
                printf(" %hhu, (left-top)", header->order); 
                break;
            case 48:
                printf(" %hhu, (right-top)", header->order);    
                break;
            default:
                printf(" %hhu, fault", header->order);
                break;    
            

        }
    }
}

void get_footer(FILE* myfile)
{
    char sym;
    while ((sym = (char)getchar()) != EOF)
    {
        fwrite(&sym, 1, 1, myfile);
    }
}

int main(int argc, char* argv[argc+1]){

    FILE *f = freopen(argv[1], "rb", stdin);  // input
    FILE *myfile = fopen(argv[2], "wb");


    struct header header;
    getHeader(f, myfile, &header);

    //weed is 5.3 and high is 5.4

    int pixels = header.F5_3 * header.F5_4;
    printf("pixels: %d",pixels);

    unsigned char b, g, r;
    pixel pixel[header.F5_4][header.F5_3];
    

    size_t width = (size_t)header.F5_3;
    size_t height = (size_t)header.F5_4;

    d_pixel avg[width][height];
    d_pixel dev[width][height];

    size_t kwant_pow = strtoul(argv[3], 0, 10);
    size_t kwant_kount = pow(2, kwant_pow);
    char kwant[kwant_kount];
    make_kwantyzator_r(kwant_kount, kwant);


    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < width; j++)
        {
            b = (unsigned char)getchar();
            g = (unsigned char)getchar();
            r = (unsigned char)getchar();
            pixel[i][j].R = r;
            pixel[i][j].G = g;
            pixel[i][j].B = b;
            // fwrite(&(pixel[i][j].B), sizeof(unsigned char), 1, myfile);
            // fwrite(&(pixel[i][j].G), sizeof(unsigned char), 1, myfile);
            // fwrite(&(pixel[i][j].R), sizeof(unsigned char), 1, myfile);
        }
    }

    jpeg_traverse(height, width, pixel, avg, dev);
    printf("\ni bastian \n");
    c_pixel kwanted_diffs[height][width];
    struct pixel output[height][width];

    DPCM(height, width, kwant_kount, avg, kwant, kwanted_diffs, output);
    

    printf("\ni did it ( zesralem sie) \n");

        for (size_t i = 0; i < height; i++){
            for (size_t j = 0; j < width; j++)
            {
                fwrite(&(output[i][j].B), sizeof(unsigned char), 1, myfile);
                fwrite(&(output[i][j].G), sizeof(unsigned char), 1, myfile);
                fwrite(&(output[i][j].R), sizeof(unsigned char), 1, myfile);
            }
    }


    get_footer(myfile);
    fclose(f);
    fclose(myfile);
    return 0;
}
