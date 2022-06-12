#!/bin/bash

m=$1
rm dane/unsorted_rbtree.txt

echo "size_n, comp_avg,  comp_maks, reads_avg, reads_maks, h_avg, h_final, h_maks" >> dane/unsorted_rbtree.txt

for n in {10000..100000..10000}
do
    echo "przejscie $n"
    for i in $( eval echo {1..$m} )
    do
        ./generator $n | ./rbtree >> dane/unsorted_rbtree.txt
    done
done
