#!/bin/bash

arrays="tests"
k=5
max_rand=5000000

from=100000
to=1000000
step=100000

dir_name=arrays
mkdir $dir_name

for ((i=from; i<=to; i+=step))
do
for ((j=0; j<k; j++))
do
./arr_generation $i $max_rand $RANDOM > ./$dir_name/${i}_${j}
./arr_sorting < ./$dir_name/${i}_${j} > ./$dir_name/${i}_${j}.sorted
done
done
