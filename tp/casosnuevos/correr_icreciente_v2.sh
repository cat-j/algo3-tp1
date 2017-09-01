#! /usr/bin/env bash
for i in icreciente_00_01 icreciente_00_05 icreciente_00_09 icreciente_01_01 icreciente_01_05 icreciente_01_09 icreciente_025_01 icreciente_025_05 icreciente_025_09 icreciente_05_01 icreciente_05_05 icreciente_05_09 icreciente_075_01 icreciente_075_05 icreciente_075_09 icreciente_09_01 icreciente_09_05 icreciente_09_09 icreciente_10_01 icreciente_10_05 icreciente_10_09
do
    echo "Corriendo ${i}:"
    ./silverstein_v2 < $i > "mediciones/${i}_sinpoda.csv"
done