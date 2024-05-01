#!/bin/bash

heap_tests="heap_tests"

max_rand=32767

from=100000
to=1000000
step=100000

seed=42

dir_name=heap_tests
mkdir $dir_name

for ((i=from; i<=to; i+=step))
do
./test_generator $i $max_rand $seed > ./$dir_name/${i}.
done
