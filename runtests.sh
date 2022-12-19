#!/bin/bash

make

function runningTests() {
    for i in {1..6}
    do
        echo "--- Running test${i} ---"
        ./exe ./tests/test${i} ${i}
    done
}

TESTS=false
DIFICIL=false

while [[ $# -gt 0 ]]; do
  key="$1"

  case $key in
    -t|--tests)
      TESTS=true
      shift
      ;;
    *)    # unknown option
      UNKNOWN+=("$1") # save it in an array for later
      shift # past argument
      ;;
  esac
done

if $TESTS; then
    echo "------- Running function runningTests -------"
    runningTests
fi