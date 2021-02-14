#!/bin/bash

for i in {1..100}
do
    echo run... $i
    ./run.sh test/./mutex_test
done