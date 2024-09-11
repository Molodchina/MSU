!/bin/bash

gcc for_heat-3d.c -fopenmp -DMINI_DATASET
echo MINI_DATASET
OMP_NUM_THREADS=1 ./a.out
OMP_NUM_THREADS=2 ./a.out
OMP_NUM_THREADS=4 ./a.out
OMP_NUM_THREADS=8 ./a.out

gcc for_heat-3d.c -fopenmp -DSMALL_DATASET
echo SMALL_DATASET
OMP_NUM_THREADS=1 ./a.out
OMP_NUM_THREADS=2 ./a.out
OMP_NUM_THREADS=4 ./a.out
OMP_NUM_THREADS=8 ./a.out

gcc for_heat-3d.c -fopenmp -DMEDIUM_DATASET
echo MEDIUM_DATASET
OMP_NUM_THREADS=1 ./a.out
OMP_NUM_THREADS=2 ./a.out
OMP_NUM_THREADS=4 ./a.out
OMP_NUM_THREADS=8 ./a.out

gcc for_heat-3d.c -fopenmp
echo LARGE_DATASET
OMP_NUM_THREADS=1 ./a.out
OMP_NUM_THREADS=2 ./a.out
OMP_NUM_THREADS=4 ./a.out
OMP_NUM_THREADS=8 ./a.out

gcc for_heat-3d.c -fopenmp -DEXTRALARGE_DATASET
echo EXTRALARGE_DATASET
OMP_NUM_THREADS=1 ./a.out
OMP_NUM_THREADS=2 ./a.out
OMP_NUM_THREADS=4 ./a.out
OMP_NUM_THREADS=8 ./a.out
