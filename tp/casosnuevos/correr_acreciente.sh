#! /usr/bin/env bash

for i in acreciente_00 acreciente_025 acreciente_05 acreciente_075 acreciente_0875 acreciente_10
do
    echo "Corriendo ${i}:"
    ./silverstein_sinpoda < $i > "mediciones/${i}_sinpoda.csv"
    ./silverstein_poda1 < $i > "mediciones/${i}_poda1.csv"
    ./silverstein_poda2 < $i > "mediciones/${i}_poda2.csv"
    ./silverstein_poda1_poda2 < $i > "mediciones/${i}_poda1_poda2.csv"
done

# echo "Corriendo acreciente_00:"
# ./silverstein_v2 < acreciente_00 > mediciones/acreciente_00_sinpoda.csv
# echo "Corriendo acreciente_001:"
# ./silverstein_v2 < acreciente_001 > mediciones/acreciente_001_sinpoda.csv
# echo "Corriendo acreciente_01:"
# ./silverstein_v2 < acreciente_01 > mediciones/acreciente_01_sinpoda.csv
# echo "Corriendo acreciente_025:"
# ./silverstein_v2 < acreciente_025 > mediciones/acreciente_025_sinpoda.csv
# echo "Corriendo acreciente_05:"
# ./silverstein_v2 < acreciente_05 > mediciones/acreciente_05_sinpoda.csv
# echo "Corriendo acreciente_075:"
# ./silverstein_v2 < acreciente_075 > mediciones/acreciente_075_sinpoda.csv
# echo "Corriendo acreciente_09:"
# # ./silverstein_v2 < acreciente_09 > mediciones/acreciente_09_sinpoda.csv
# # echo "Corriendo acreciente_099:"
# # ./silverstein_v2 < acreciente_099 > mediciones/acreciente_099_sinpoda.csv
# echo "Corriendo acreciente_10:"
# ./silverstein_v2 < acreciente_10 > mediciones/acreciente_10_sinpoda.csv
