#!/bin/bash

for i in {1..15}
do
        for j in {0..1000}
        do
                ./gentestseed $i | ./QuickSortTest
        done
done
