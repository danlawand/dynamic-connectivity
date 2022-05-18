#!/bin/bash

for i in {2..9}
do
    echo "Running copy of test1 in test${i}"
    cp expected_test1 expected_test${i}
done