#!/bin/bash

m=$1

rm dane/BS_poczatek_m$m.txt
rm dane/BS_koniec_m$m.txt
rm dane/BS_srodek_m$m.txt
rm dane/BS_losowy_m$m.txt


echo "n porównania czas" >> dane/BS_poczatek_m$m.txt
echo "n porównania czas" >> dane/BS_koniec_m$m.txt
echo "n porównania czas" >> dane/BS_srodek_m$m.txt
echo "n porównania czas" >> dane/BS_losowy_m$m.txt


for n in {1000..100000..1000}
do
    echo "przejscie $n"
    for i in $( eval echo {1..$m})
    do
        ./generator $n >> dane/randomtab.txt
        # 'blisko początku'
        cat dane/randomtab.txt | ./BS 1 >> dane/BS_poczatek_m$m.txt      
        # 'blisko końca'
        cat dane/randomtab.txt | ./BS 2 >> dane/BS_koniec_m$m.txt
        # 'okolo środka'
        cat dane/randomtab.txt | ./BS 3 >> dane/BS_srodek_m$m.txt
        # 'losowy z całej tablicy'
        cat dane/randomtab.txt | ./BS 0 >> dane/BS_losowy_m$m.txt

        rm dane/randomtab.txt
    done
done
