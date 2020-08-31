#!/bin/bash

# Simple bash script to run and test

# Compile
g++ -Wall -Werror -std=c++14 -O -o out/program *.cpp

# Move to tests folder
cd out

# Run
./program

# Remove program
rm program

# Go back to previous directory
cd ..

exit 0;