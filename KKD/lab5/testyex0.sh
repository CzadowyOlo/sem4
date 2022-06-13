#!/bin/bash

m=$1

for i in $( eval echo {1..$m} )
    do
        for j in {1..6..1}
        do
            ./kwant ./testy4/example0.tga ./example0/ex0_colorspow_{$i}_case{$j}.tga $i
        done
    done