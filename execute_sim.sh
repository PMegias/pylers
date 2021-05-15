export OMP_NUM_THREADS=3

make clean
make build

echo "0,0" > res/poblacion.csv
echo "0,0" > res/nacimiento.csv
echo "0,0" > res/morticion.csv


perf stat ./build

rm res/*.png