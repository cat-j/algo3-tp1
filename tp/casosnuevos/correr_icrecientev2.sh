#! /usr/bin/env bash
for i in icreciente_00_00 icreciente_00_025 icreciente_00_05 icreciente_00_075 icreciente_00_0875 icreciente_00_10 icreciente_025_00 icreciente_025_025 icreciente_025_05 icreciente_025_075 icreciente_025_0875 icreciente_05_00 icreciente_05_025 icreciente_05_05 icreciente_05_075 icreciente_05_0875 icreciente_075_00 icreciente_075_025 icreciente_075_05 icreciente_075_075 icreciente_075_0875 icreciente_0875_00 icreciente_0875_025 icreciente_0875_05 icreciente_0875_075 icreciente_0875_0875 icreciente_10_00 icreciente_10_025 icreciente_10_05 icreciente_10_075 icreciente_10_0875 

do
    echo "Corriendo ${i}:"
    ./silverstein_sinpoda < $i > "mediciones/${i}_sinpoda.csv"
    ./silverstein_poda1 < $i > "mediciones/${i}_poda1.csv"
    ./silverstein_poda2 < $i > "mediciones/${i}_poda2.csv"
    ./silverstein_poda1_poda2 < $i > "mediciones/${i}_poda1_poda2.csv"
done