#!/bin/bash

export OMP_NUM_THREADS=2

make clean
make build

echo "0,0" > res/poblacion.csv
echo "0,0" > res/nacimiento.csv
echo "0,0" > res/morticion.csv

./build &> /dev/null

rm res/*.png
