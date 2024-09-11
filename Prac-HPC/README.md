# Development of a Parallel Version of a Program for Heat Distribution in Three-Dimensional Space

---

## Problem Statement

The task of modifying the temperature within liquid, solid, or hollow three-dimensional objects, while considering the thermal conductivity of materials, involves taking into account the neighboring sections and their temperatures' effects on the temperature of the specified section.

In this problem, we represent the solid as a three-dimensional array of size `n x n x n`, where the temperature of the cell with indices `(i, j, k)` will be influenced by neighboring cells with indices:

- `(i-1, j, k)`
- `(i+1, j, k)`
- `(i, j-1, k)`
- `(i, j+1, k)`
- `(i, j, k-1)`
- `(i, j, k+1)`

We observe temperature propagation over a duration of `tsteps` discrete time steps. The objective of this work is to accelerate the execution of the program through data parallelization.

---

## Sequential Algorithm

The problem of calculating the three-dimensional temperature distribution within the solid can be reduced to executing `(n - 2) * (n - 2) * (n - 2)` independent temperature calculations for the cells, requiring `7 * n * n * n * TSteps` summations of cell values. The computational complexity is characterized by `O(n^3)`.

The algorithm for calculating the cells of the matrix is iterative. To compute all elements of matrix A with dimensions `n x n x n`, the time required is given by the formula:

\[
T = (n - 2) * (n - 2) * (n - 2) * 7 * t 
\]

where `t` represents the time taken for one elementary scalar operation.

### Results of the Sequential Algorithm

![Results of the Sequential Algorithm](https://github.com/Molodchina/MSU/blob/main/Prac-HPC/docs/normal.jpg)

---

## Parallel Algorithm

Initially, we observed that the algorithm could be sped up even without parallelization:

1. In the function `kernel_heat_3d`, we optimized the computation of cell temperatures by eliminating redundant calculations and memory accesses.
2. In the `init_array` function, we achieved optimization by modifying the operation from `(... + n - ...) * 10 / n → 10 + ...`.

### OpenMP FOR Directive

We will utilize nested parallelism. Let each new declaration of a parallel section split the execution thread into `q` threads.

We will also parallelize the function `kernel_head_3d`. This function performs calculations on matrices A and B using several parallel threads, with each thread executing calculations on a distinct element of the matrices.

#### Results for FOR Directive

![Results for PARALLEL FOR Directive](https://github.com/Molodchina/MSU/blob/main/Prac-HPC/docs/for.jpg)

---

### OMP Task

We will employ a task-based parallelism approach. Let each new computation of temperatures distribute the execution thread into `q` threads.

#### Results for TASK Directive

![Results for PARALLEL TASK Directive](https://github.com/Molodchina/MSU/blob/main/Prac-HPC/docs/task.jpg)

---

## Conclusion

As evidenced by the comparison with the sequential algorithm, OpenMP provides performance advantages in execution time primarily for sufficiently large matrix dimensions (starting from approximately 40). Conversely, for smaller matrix sizes, parallelization tends to perform poorly due to overhead associated with thread creation.

Furthermore, it is noticeable that the optimal number of threads increases with the growth of matrix dimensions.

For both TASK and FOR directives, we observed that execution time decreases as the number of threads increases from 1 to 60. However, a slight increase in execution time occurs between 60 and 80 threads, after which the time begins to decrease again as the number of threads rises to 160.

---

## MPI

We will utilize a communication framework for inter-thread interactions in the parallel program.

Initially, we conceptualize an algorithm for distributing temperature calculations across threads: ideally, each thread is assigned one "square." If the number of threads is fewer than the number of squares, each thread will handle `(n * (rank + 1)) / numtasks` squares, where `n` is the dimension of the cube, `rank` is the current thread number, and `numtasks` represents the total number of threads engaged in the computation.

However, this approach leads to the presence of "shadow edges," which are borders calculated in other processes. To address this, we implement an interface for communication between the thread and its neighboring threads to compute accurate values for the matrix cells.
