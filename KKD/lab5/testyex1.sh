#!/bin/bash

m=$1

for i in $( eval echo {1..$m} )
    do
        for j in {1..6..1}
        do
            ./kwant ./testy4/example1.tga ./ex1_ep1/ex1_colorspow_{$i}_case{$j}.tga $i
        done
    done