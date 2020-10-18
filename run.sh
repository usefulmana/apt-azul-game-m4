#!/bin/bash

# Simple bash script to run and test

# shellcheck disable=SC2164
cd src

#sudo make clean

# Compile
sudo make

# Move to tests folder
cd bin

if [ "$1" == "test" ]; then
  ./azul -t "$2"
elif [ "$1" == "ran" ]; then
  ./azul -s "$2"
  elif [ "$1" == "adv" ]; then
  ./azul --adv
else
  #valgrind --leak-check=full ./azul
  ./azul
fi

# Valgrind
# valgrind --leak-check=full ./azul

# Debug
# gdb azul

# Go back to previous directory
cd ../..

exit 0;
