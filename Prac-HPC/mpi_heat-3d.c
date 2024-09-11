/* Include benchmark-specific header. */
#include "heat-3d.h"
#include <stdbool.h>
#include <mpi.h>


MPI_Request req[4];
MPI_Status stat[4];
int numtasks, rank;

static
void init_array (int n,
    int amount,
    int start,
    float A[amount + 2][n][n],
    float B[amount + 2][n][n])
{
  int i, j, k;

  for (i = 1; i <= amount; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        A[i][j][k] = B[i][j][k] = 10. + (float) (start + i + j - k)* 10 / (n);
}

static
void print_array(int n,
   float A[n][n][n])

{
  int i, j, k;

  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "A");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++) {
         if ((i * n * n + j * n + k) % 20 == 0) fprintf(stderr, "\n");
         fprintf(stderr, "%0.2f ", A[i][j][k]);
      }
  fprintf(stderr, "\nend   dump: %s\n", "A");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static
void kernel_heat_3d(int tsteps,
        int n,
        int amount,
        float A[amount + 2][n][n],
        float B[amount + 2][n][n])
{
    int count, pos_mask, t, i, j, k;

    for (t = 1; t <= TSTEPS; t++) {

        count = 0;
        pos_mask = 0;
        if (rank != 0) {
            MPI_Isend(&A[1][0][0], n * n, MPI_FLOAT, rank - 1, 1, MPI_COMM_WORLD, &req[0]);
            MPI_Irecv(&A[0][0][0], n * n, MPI_FLOAT, rank - 1, 2, MPI_COMM_WORLD, &req[1]);
            count += 2;
            pos_mask += 1;
        }
        if (rank + 1 != numtasks) {
            MPI_Isend(&A[amount][0][0], n * n, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD, &req[2]);
            MPI_Irecv(&A[amount + 1][0][0], n * n, MPI_FLOAT, rank + 1, 1, MPI_COMM_WORLD, &req[3]);
            count += 2;
            pos_mask += 2;
        }

        for (i = 1; i <= amount; i++) {
            for (j = 1; j < n-1; j++) {
                for (k = 1; k < n-1; k++) {
                    B[i][j][k] = 0.125f * (A[i][j+1][k] + A[i][j-1][k])
                                 + 0.125f * (A[i][j][k+1] + A[i][j][k-1])
                                 + 0.25f * A[i][j][k];
                    if (i != 1)
                        B[i][j][k] += 0.125f * (A[i-1][j][k]);
                    if (i != amount)
                        B[i][j][k] += 0.125f * (A[i+1][j][k]);
                }
            }
        }

        if (numtasks > 1) {
            int pos = (pos_mask == 2) ? 2 : 0;
            MPI_Waitall(count, &req[pos], &stat[pos]);
        }

        for (j = 1; j < n-1; j++)
            for (k = 1; k < n-1; k++)
                B[1][j][k] += 0.125f * A[0][j][k];

        for (j = 1; j < n-1; j++)
            for (k = 1; k < n-1; k++)
                B[amount][j][k] += 0.125f * A[amount + 1][j][k];

        count = 0;
        pos_mask = 0;
        if (rank != 0) {
            MPI_Isend(&B[1][0][0], n * n, MPI_FLOAT, rank - 1, 1, MPI_COMM_WORLD, &req[0]);
            MPI_Irecv(&B[0][0][0], n * n, MPI_FLOAT, rank - 1, 2, MPI_COMM_WORLD, &req[1]);
            count += 2;
            pos_mask += 1;
        }
        if (rank + 1 != numtasks) {
            MPI_Isend(&B[amount][0][0], n * n, MPI_FLOAT, rank + 1, 2, MPI_COMM_WORLD, &req[2]);
            MPI_Irecv(&B[amount + 1][0][0], n * n, MPI_FLOAT, rank + 1, 1, MPI_COMM_WORLD, &req[3]);
            count += 2;
            pos_mask += 2;
        }

       for (i = 1; i <= amount; i++) {
            for (j = 1; j < n-1; j++) {
                for (k = 1; k < n-1; k++) {
                    A[i][j][k] = 0.125f * (B[i][j+1][k] + B[i][j-1][k])
                                + 0.125f * (B[i][j][k+1] + B[i][j][k-1])
                                + 0.25f * B[i][j][k];
                    if (i != 1)
                        A[i][j][k] += 0.125f * (B[i-1][j][k]);
                    if (i != amount)
                        B[i][j][k] += 0.125f * (B[i+1][j][k]);
                }
            }
        }
        
        if (numtasks > 1) {
            int pos = (pos_mask == 2) ? 2 : 0;
            MPI_Waitall(count, &req[pos], &stat[pos]);
        }

        for (j = 1; j < n-1; j++)
            for (k = 1; k < n-1; k++)
                A[1][j][k] += 0.125f * B[0][j][k];

        for (j = 1; j < n-1; j++)
            for (k = 1; k < n-1; k++)
                A[amount][j][k] += 0.125f * B[amount + 1][j][k];

    }
}


int main(int argc, char** argv)
{
    int n = N;
    int tsteps = TSTEPS;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    // printf("RANK: %d (%d)", rank, numtasks);

    if (rank > n) {
        MPI_Abort(MPI_COMM_WORLD, 2);
    }
    
    int start, last, amount;
    start = (n * rank) / numtasks;
    last = (n * (rank + 1)) / numtasks - 1;
    amount = last - start + 1;
    // printf("-> %d %d %d", start, last, amount);

    float (*A)[amount + 2][n][n];
    float (*B)[amount + 2][n][n];

    A = (float(*)[amount + 2][n][n])malloc ((amount + 2) * (n) * (n) * sizeof(float));
    B = (float(*)[amount + 2][n][n])malloc ((amount + 2) * (n) * (n) * sizeof(float));
    
    init_array (n, amount, start, *A, *B);

    MPI_Barrier(MPI_COMM_WORLD);

    double time_start;
    if (rank == 0) {
        time_start = MPI_Wtime();
    }

    kernel_heat_3d (tsteps, n, amount, *A, *B);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) { 
        printf ("Time in seconds = %0.6lf\n", MPI_Wtime() - time_start);
    }

    // if (argc > 42 && ! strcmp(argv[0], "")) print_array(n, *A);

    MPI_Finalize();

    free(A);
    free(B);

    return 0;
}