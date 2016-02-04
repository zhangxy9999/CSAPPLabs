/*
 * Rain Xuanyu Zhang
 * zhan2223
 * ID: 4642453
 *
 * A Matrix Wavefront Transport Function
 *
 * trans.c - Matrix Wavefront A[i][j] = A[i-1][j-1] + A[i-1][j] + A[i][j-1]
 *
 * Each matrix wavefront transport function must have a prototype of the form:
 * void matrix_wavefront(int M, int N, int A[M][N]);
 *
 * A matrix wavefront transport function is evaluated by counting the number of misses
 * on a 512B and 4KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_matrix_wavefront(int M, int N, int A[M][N], int s, int E, int b);
char matrix_wavefront_submit_desc[] = "Matrix Wavefront submission";
void matrix_wavefront_submit(int M, int N, int A[M][N], int s, int E, int b)
{
    int i, j,ii,jj;
    int d = 51; //block size is 51

    if(s == 5) {
        for (ii = 1; ii < M - d + 1; ii += d) {
            for (jj = 1; jj < N - d + 1; jj += d) {
                for (i = ii; i < ii + d; i++) {
                    for (j = jj; j < jj + d; j++) {
                        A[i][j] = A[i-1][j-1] + A[i-1][j] + A[i][j-1];
                    }
                }
            }
        }
    }

    if(s == 8) {
        for (i = 1; i < M; i++) {
            for (j = 1; j < N; j++) {
                A[i][j] = A[i-1][j-1] + A[i-1][j] + A[i][j-1];
            }
        }
    }
}

void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(matrix_wavefront_submit, matrix_wavefront_submit_desc);
}

/*
 * is_matrix_wavefront - This helper function checks if matrix wavefront A is generated by above
 * definition . You can check the correctness of your matrix wavefront by calling
 *     it before returning from the matrix wavefront function.
 */
int is_matrix_wavefront(int M, int N, int A[M][N], int s, int E, int b)
{
    int i, j;

    for (i = 1; i < N; i++) {
        for (j = 1; j < M; ++j) {
            if (A[i][j] != (A[i-1][j-1] + A[i-1][j] + A[i][j-1]) ) {
                return 0;
            }
        }
    }
    return 1;
}

