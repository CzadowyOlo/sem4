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

int modulo(int x, int y){
    int z = x%y;
    if (z >= 0){
        return z;
    }
    else{
        return y + z;
    }
}

int main(){

    // int x = 6;
    // int y = 9;

    // cout<<min(x,y)<<" "<<max(x,y)<<endl;
    // cout<<((x - y)%8)<<endl;
    // cout<<((y-x)%8)<<endl;

    // cout<<modulo(x-y, 8)<<endl;
    // cout<<modulo(y-x, 8)<<endl;
    struct cipa{
        int a;
        int b;
        int c;
    }

    struct cipa chuj = { .a = 12, .b = 69, .c = 0};
    chuj = chuj + 3;
    cout<<chuj.a<<", "<<chuj.b<<", "<<chuj.c<<endl;
    return 0;
}