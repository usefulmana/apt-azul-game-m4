#!/bin/bash

# Simple bash script to run and test

cd src

#sudo rm -rf obj

# Compile
sudo make

# Move to tests folder
cd bin

# Debug
#gdb azul

# Run
#./azul
# shellcheck disable=SC2154
if [ "$1" == "test" ]; then
  ./azul -t test.txt
else
  valgrind --leak-check=full ./azul
fi


# Go back to previous directory
cd ..

cd ..

exit 0;