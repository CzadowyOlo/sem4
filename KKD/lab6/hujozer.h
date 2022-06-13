#ifndef HUJOZER_H
#define HUJOZER_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pixel
{
    uint8_t B;
    uint8_t G;
    uint8_t R;
    char pad[5];
   
} pixel; 

typedef struct d_pixel
{
    double B;
    double G;
    double R;
   
} d_pixel; 

typedef struct c_pixel
{
    char B;
    char G;
    char R;
   
} c_pixel; 

typedef struct header
{
    uint8_t F1; // number of bits in F6  || size: 1 byte
    uint8_t F2; // define if F7 exist. It is 0 or 1 || size: 1 byte
    uint8_t F3; // || size: 1 byte
    uint8_t F5_5; // pixel depth - how many bits per pixel. f.e. 24 || size: 1 byte
    uint8_t F5_6; // descriptor - bit 4: left-right, bit 5: top-bottom || size: 1 byte
    uint8_t order; // this is 4th and 5th bit of F5_6
    uint8_t F4_3; // color map entry size - bits per entry || size: 1 byte || ex: 15, 16, 24, 32  | F4_3 * F4_2 define size of F7
    char srad[1];
    uint16_t F4_1; // starting entry in color map || size: 2 bytes
    uint16_t F4_2; // color map length - number of entries || size: 2 bytes
    uint16_t F5_1; // spawn X || size: 2 bytes
    uint16_t F5_2; // spawn Y || size: 2 bytes
    uint16_t F5_3; // image width || size: 2 bytes
    uint16_t F5_4; // image height || size: 2 bytes  
    char pad[4];
} header;

void get_footer(FILE* myfile);
double maksimum(double a, double b, double c);
void getHeader(FILE* f, FILE* myfile, header *header);
double modulo(double x);
void jpeg_traverse(size_t row, size_t column, pixel map[row][column], d_pixel avg[row][column], d_pixel dev[row][column]);

#endif
