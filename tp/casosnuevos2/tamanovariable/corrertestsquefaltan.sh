#! /usr/bin/env bash

for i in {1..9}
  do
  for test in TEST_${i}agentes*
    do
      echo "Corriendo test " ${test}_sinpoda
     ./silverstein_sinpoda < ${test} > mediciones/${test}_sinpoda.csv
    done
  done
