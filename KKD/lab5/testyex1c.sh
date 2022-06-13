#!/bin/bash

m=$1

for i in $( eval echo {1..$m} )
    do
        for j in {1..6..1}
        do
            ./kwantc ./testy4/example1.tga ./ex1_centrum/ex1_colorspow_{$i}_case{$j}.tga $i
        done
    done