#!/bin/bash

make

for i in {1..13}
do
    echo "Running test${i}.txt"
    ./exe ./test/tests/test${i}.txt ${i} v
done