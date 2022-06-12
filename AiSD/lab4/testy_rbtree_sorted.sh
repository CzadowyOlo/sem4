#!/bin/bash

m=$1
rm dane/sorted_rbtree.txt

echo "size_n, comp_avg,  comp_maks, reads_avg, reads_maks, h_avg, h_final, h_maks" >> dane/sorted_rbtree.txt

for n in {10000..100000..10000}
do
    echo "przejscie $n"
    for i in $( eval echo {1..$m} )
    do
        ./asco_generator $n | ./rbtree >> dane/sorted_rbtree.txt
    done
done
