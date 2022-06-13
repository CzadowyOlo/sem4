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

struct cipa{
        int a;
        int b;
        int c;
    };

int modulo(int x, int y){
    int z = x%y;
    if (z >= 0){
        return z;
    }
    else{
        return y + z;
    }
}

void dodawanie(struct cipa *chuj, int e){
    (chuj->a) += e;
    (chuj->b) += e;
    (chuj->c) += e;
}

int main(){

    struct cipa chuj = { .a = 12, .b = 69, .c = 0};
    dodawanie(&chuj, 3);
    cout<<chuj.a<<", "<<chuj.b<<", "<<chuj.c<<endl;
    return 0;
}

//        w1: 128-e, 128-e, 128-e
//        w2: 128+e, 128+e, 128+e

// kolejna pentla
//        p1: 129, 129, 129 --> w2
//        p2  127, 127, 127 --> w1
//      itd p3, p4, pchuj
//    zbiór w1: p2, p4, p10
//    zbiór w2: p1, p3, p6

//    w1 = avg ze zbioru w1
//    w2 = avg ze zbioru w2

// wracamy do splittingu z nowym w1 i w2