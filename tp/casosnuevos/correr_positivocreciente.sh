#! /usr/bin/env bash
for i in positivocreciente_00 positivocreciente_025 positivocreciente_05 positivocreciente_075 positivocreciente_0875 positivocreciente_10
do
    echo "Corriendo ${i}:"
    ./silverstein_sinpoda < $i > "mediciones/${i}_sinpoda.csv"
    ./silverstein_poda1 < $i > "mediciones/${i}_poda1.csv"
    ./silverstein_poda2 < $i > "mediciones/${i}_poda2.csv"
    ./silverstein_poda1_poda2 < $i > "mediciones/${i}_poda1_poda2.csv"
done

# echo "Corriendo positivocreciente_00:"
# ./silverstein_v2 < positivocreciente_00 > mediciones/positivocreciente_00_sinpoda.csv
# # echo "Corriendo positivocreciente_001:"
# # ./silverstein_v2 < positivocreciente_001 > mediciones/positivocreciente_001_sinpoda.csv
# # echo "Corriendo positivocreciente_01:"
# # ./silverstein_v2 < positivocreciente_01 > mediciones/positivocreciente_01_sinpoda.csv
# echo "Corriendo positivocreciente_025:"
# ./silverstein_v2 < positivocreciente_025 > mediciones/positivocreciente_025_sinpoda.csv
# echo "Corriendo positivocreciente_05:"
# ./silverstein_v2 < positivocreciente_05 > mediciones/positivocreciente_05_sinpoda.csv
# echo "Corriendo positivocreciente_075:"
# ./silverstein_v2 < positivocreciente_075 > mediciones/positivocreciente_075_sinpoda.csv
# # echo "Corriendo positivocreciente_09:"
# # ./silverstein_v2 < positivocreciente_09 > mediciones/positivocreciente_09_sinpoda.csv
# echo "Corriendo positivocreciente_0875:"
# ./silverstein_v2 < positivocreciente_0875 > mediciones/positivocreciente_099_sinpoda.csv
# echo "Corriendo positivocreciente_10:"
# ./silverstein_v2 < positivocreciente_10 > mediciones/positivocreciente_10_sinpoda.csv
