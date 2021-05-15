export OMP_NUM_THREADS=2

make clean
make build
 
perf stat ./build