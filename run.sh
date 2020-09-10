#!/bin/bash

# Simple bash script to run and test

cd src

sudo rm -rf obj

# Compile
sudo make

# Move to tests folder
cd bin

# Run
./azul

# Go back to previous directory
cd ..

cd ..

exit 0;