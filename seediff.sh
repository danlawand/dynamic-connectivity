#!/bin/bash

function whichDifference() {
    mkdir ./tests/diff
    for i in {1..8}
    do
        echo "Comparining answer_test${i} with result_test${i}"
        diff -u ./tests/answers/answer_test${i} ./tests/results/result_test${i} > ./tests/diff/difference${i}
    done
}



function failedOrSucessed() {
    for i in {1..8}
    do
        if cmp --silent -- ./tests/answers/answer_test${i} ./tests/results/result_test${i}; then
        echo "Test${i} Sucessed!"
        else
        echo "Test${i} FAILED!"
        fi
    done
}

SUCESS=false
DIFFERENCE=false

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -s|--sucess)
      SUCESS=true
      shift
      ;;
    -d|--difference)
      DIFFERENCE=true
      shift
      ;;
    *)    # unknown option
      UNKNOWN+=("$1") # save it in an array for later
      shift # past argument
      ;;
  esac
done

if $DIFFERENCE; then
    echo "------- Running function whichDifference -------"
    whichDifference
fi


if $SUCESS; then
    echo "------- Running function failedOrSucessed -------"
    failedOrSucessed
fi