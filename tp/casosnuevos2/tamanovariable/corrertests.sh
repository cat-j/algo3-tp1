#! /usr/bin/env bash

for v in _sinpoda 
  do
  for test in TEST*
    do
    echo "Corriendo test " ${test}${sinpoda}
      ./silverstein${v} < ${test} > mediciones/${test}${v}.csv
    done
  done
