#! /usr/bin/env bash
for i in icreciente_05_10

do
    echo "Corriendo ${i}:"
    ./silverstein_sinpoda < $i > "mediciones/${i}_sinpoda.csv"
    ./silverstein_poda1 < $i > "mediciones/${i}_poda1.csv"
    ./silverstein_poda2 < $i > "mediciones/${i}_poda2.csv"
    ./silverstein_poda1_poda2 < $i > "mediciones/${i}_poda1_poda2.csv"
done