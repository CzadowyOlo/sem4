#ifndef KWANTYZER_H
#define KWANTYZER_H

#include <stddef.h>
#include <vector>

typedef struct pixel
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
    size_t index_centroida;
    char pad[4];
   
} pixel; 

typedef struct coloroids{
    double b;
    double g;
    double r; // ja za moment
    double r_pixel;   // sumaować pixele po kolei
    double g_pixel;   // sumaować pixele po kolei
    double b_pixel;  // sumaować pixele po kolei
    size_t pixel_tab_size;

} coloroids;

typedef struct header
{
    //specific information from header--------------------------------------------------------
    uint8_t F1; // number of bits in F6  || size: 1 byte
    uint8_t F2; // define if F7 exist. It is 0 or 1 || size: 1 byte
    uint8_t F3; // || size: 1 byte
    uint16_t F4_1; // starting entry in color map || size: 2 bytes
    uint16_t F4_2; // color map length - number of entries || size: 2 bytes
    uint8_t F4_3; // color map entry size - bits per entry || size: 1 byte || ex: 15, 16, 24, 32  | F4_3 * F4_2 define size of F7
    uint16_t F5_1; // spawn X || size: 2 bytes
    uint16_t F5_2; // spawn Y || size: 2 bytes
    uint16_t F5_3; // image width || size: 2 bytes
    uint16_t F5_4; // image height || size: 2 bytes
    uint8_t F5_5; // pixel depth - how many bits per pixel. f.e. 24 || size: 1 byte
    uint8_t F5_6; // descriptor - bit 4: left-right, bit 5: top-bottom || size: 1 byte
    uint8_t order; // this is 4th and 5th bit of F5_6
    uint8_t help_operator = 48;
    // till now we have 18 bits written and that is all of header
    // in our list we assume, that F6 and F7 not exist
} header;

    // int sym; // to get 1 byte
    // int sym_1; // first byte if we have to get two bytes
    // int sym_2; // second byte if we have to get two bytes
    // number on two bytes is like we do :
    // sym_1 = getchar();
    // sym_2 = getchar();
    // sym = sym_1 * 256 + sym_2;
    //----------------------------------------------------------------------------------------
    


#endif