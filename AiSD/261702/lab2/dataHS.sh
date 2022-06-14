#!/bin/bash

for i in {100..1000}
do
        for j in {0..1000}
        do
                ./gentestseed $i | ./HybridSort
        done
done
