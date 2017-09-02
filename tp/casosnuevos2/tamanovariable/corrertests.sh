#! /usr/bin/env bash

for v in _sinpoda _poda1 _poda2 _poda1_poda2
  do
  for test in TEST*
    do
    echo "Corriendo test " ${test}${sinpoda}
      ./silverstein${v} < ${test} > mediciones/${test}${v}.csv
    done
  done
