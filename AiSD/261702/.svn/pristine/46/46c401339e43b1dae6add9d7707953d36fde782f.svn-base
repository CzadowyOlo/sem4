#!/bin/bash

m=$1

rm dane/QS_worst_m$m.txt
rm dane/QSU_worst_m$m.txt



echo "n porównania przestawienia czas" >> dane/QS_worst_m$m.txt
echo "n porównania przestawienia czas" >> dane/QSU_worst_m$m.txt



for n in {100..100000..100}
do
    echo "przejscie $n"
    for i in $( eval echo {1..$m})
    do
        ./desc $n >> dane/randomtab.txt
        # 'blisko początku'
        cat dane/randomtab.txt | ./QS >> dane/QS_worst_m$m.txt      
        # 'blisko końca'
        cat dane/randomtab.txt | ./QSU >> dane/QSU_worst_m$m.txt

        rm dane/randomtab.txt
    done
done
