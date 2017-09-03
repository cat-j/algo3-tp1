#! /usr/bin/env bash

for v in sinpoda poda1 poda2 poda1_poda2
do
	for i in {1..30}
	do
		for p in 075 0875 099 10
		do
			for test in TEST_${i}agentes_${p}negativo
			do
				echo "Corriendo " ${test}_${v} | tee -a "log"
				./silverstein_${v} < ${test} > mediciones/${test}_${v}.csv
			done
		done
	done
done
