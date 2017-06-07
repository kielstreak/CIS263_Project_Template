#!/usr/bin/env bash

SORTING_ALG=5

for vec_size in 100 1000 10000 100000 1000000
do
        echo "Size $vec_size"
        for i in {1..10}
        do
                echo "=====>Iteration $i"
                time ./a.out $vec_size $SORTING_ALG
        done
        echo "========================================"
done
