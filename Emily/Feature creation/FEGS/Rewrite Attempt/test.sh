#! /usr/bin/bash

source_file=FEGS

g++ $source_file.cpp -o $source_file

./$source_file

rm ./$source_file