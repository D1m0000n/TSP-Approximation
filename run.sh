#!/bin/bash
rm -r $PWD/test_generator/generator
g++ $PWD/test_generator/generator.cpp -o $PWD/test_generator/generator
rm -r build-dir
mkdir build-dir
cd  build-dir
cmake ..
make
$PWD/../test_generator/generator | $PWD/TSP
