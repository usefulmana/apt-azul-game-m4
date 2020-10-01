#!/bin/bash

# Simple bash script to run and test

# shellcheck disable=SC2164
cd src

#sudo rm -rf obj

# Compile
sudo make

# Move to tests folder
cd bin

if [ "$1" == "test" ]; then
  ./azul -t test.txt
else
  ./azul
fi

# Valgrind
# valgrind --leak-check=full ./azul

# Debug
# gdb azul

# Go back to previous directory
cd ../..

exit 0;