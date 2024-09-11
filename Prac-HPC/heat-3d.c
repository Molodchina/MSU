/* Include benchmark-specific header. */
#include "heat-3d.h"
#define MINI_DATASET

double bench_t_start, bench_t_end;

static
double rtclock()
{
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, NULL);
    if (stat != 0)
      printf ("Error return from gettimeofday: %d", stat);
    return (Tp.tv_sec + Tp.tv_usec * 1.0e-6);
}

void bench_timer_start()
{
  bench_t_start = rtclock ();
}

void bench_timer_stop()
{
  bench_t_end = rtclock ();
}

void bench_timer_print()
{
  printf ("Time in seconds = %0.6lf\n", bench_t_end - bench_t_start);
}


static
void init_array (int n,
   float A[ n][n][n],
   float B[ n][n][n])
{
  int i, j, k;

  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++)
        A[i][j][k] = B[i][j][k] = (float) (i + j + (n-k))* 10 / (n);
}

static
void print_array(int n,
   float A[ n][n][n])

{
  int i, j, k;

  fprintf(stderr, "==BEGIN DUMP_ARRAYS==\n");
  fprintf(stderr, "begin dump: %s", "A");
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      for (k = 0; k < n; k++) {
         if ((i * n * n + j * n + k) % 20 == 0) printf("\n");
         printf("%0.2f ", A[i][j][k]);
      }
  fprintf(stderr, "\nend   dump: %s\n", "A");
  fprintf(stderr, "==END   DUMP_ARRAYS==\n");
}

static
void kernel_heat_3d(int tsteps,
        int n,
        float A[ n][n][n],
        float B[ n][n][n])
{
    int t, i, j, k;

    for (t = 1; t <= TSTEPS; t++) {
        for (i = 1; i < n-1; i++) {
            for (j = 1; j < n-1; j++) {
                for (k = 1; k < n-1; k++) {
                    B[i][j][k] = 0.125f * (A[i+1][j][k] - 2.0f * A[i][j][k] + A[i-1][j][k])
                                 + 0.125f * (A[i][j+1][k] - 2.0f * A[i][j][k] + A[i][j-1][k])
                                 + 0.125f * (A[i][j][k+1] - 2.0f * A[i][j][k] + A[i][j][k-1])
                                 + A[i][j][k];
                }
            }
        }
        for (i = 1; i < n-1; i++) {
           for (j = 1; j < n-1; j++) {
               for (k = 1; k < n-1; k++) {
                   A[i][j][k] = 0.125f * (B[i+1][j][k] - 2.0f * B[i][j][k] + B[i-1][j][k])
                                + 0.125f * (B[i][j+1][k] - 2.0f * B[i][j][k] + B[i][j-1][k])
                                + 0.125f * (B[i][j][k+1] - 2.0f * B[i][j][k] + B[i][j][k-1])
                                + B[i][j][k];
               }
           }
       }
    }
}


int main(int argc, char** argv)
{
  int n = 40;
  int tsteps = 100;
  printf("%d %d", n, tsteps);
  float (*A)[n][n][n]; A = (float(*)[n][n][n])malloc ((n) * (n) * (n) * sizeof(float));
  float (*B)[n][n][n]; B = (float(*)[n][n][n])malloc ((n) * (n) * (n) * sizeof(float));

  init_array (n, *A, *B);

  bench_timer_start();

  kernel_heat_3d (tsteps, n, *A, *B);

  bench_timer_stop();
  bench_timer_print();

  if (argc > 42 && ! strcmp(argv[0], "")) print_array(n, *A);
  
  print_array(n, *A);
  
  free((void*)A);
  free((void*)B);

  return 0;
}
