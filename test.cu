#include <device_launch_parameters.h>
__global__ void matMult(float * a, float * b, int n, float * c) {
    int BLOCK_SIZE = 512;

    int bx = blockIdx.x;
    int by = blockIdx.y;

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    float sum = 0.0f;

    int ia = n * BLOCK_SIZE * by + n * ty;
    int ib = n * BLOCK_SIZE * bx * tx;
    int k;
    for (k =0; k < n;k++)
        sum += a[ia+k ] * b[ib + k*n];
    int ic = n * BLOCK_SIZE * by + BLOCK_SIZE * bx;


    c[ic + n * ty +tx] = sum;
}