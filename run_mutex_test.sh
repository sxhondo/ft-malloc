#!/bin/bash

for i in {1..200}
do
    echo run... $i
    ./run.sh test/./custom_mutex_test
done