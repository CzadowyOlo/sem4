#!/bin/bash

m=$1
rm dane/unsorted_bst.txt

echo "size_n, comp_avg,  comp_maks, reads_avg, reads_maks, h_avg,   h_final   h_maks \n" >> dane/unsorted_bst.txt

for n in {10000..1000000..10000}
do
    echo "przejscie $n"
    for i in $( eval echo {1..$m} )
    do
        ./generator $n | ./bst >> dane/unsorted_bst.txt
    done
done
