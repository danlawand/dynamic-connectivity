#!/bin/bash

NTESTS=$12

function whichDifference() {
    for i in {1..13}
    do
        echo "Comparining expected_test${i} with result_test${i}"
        diff -u ./test/expected_results/expected_test${i} ./test/result_test/result_test${i} > ./test/diff_test/difference${i}
    done
}



function failedOrSucessed() {
    for i in {1..13}
    do
        if cmp --silent -- ./test/expected_results/expected_test${i} ./test/result_test/result_test${i}; then
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
    echo "--- Running function whichDifference ---"
    whichDifference
fi


if $SUCESS; then
    echo "--- Running function failedOrSucessed ---"
    failedOrSucessed
fi
