#include "ex2.h"
#include <omp.h>

double dotp_naive(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    for (int i = 0; i < arr_size; i++)
        global_sum += x[i] * y[i];
    return global_sum;
}

// Critical Keyword
double dotp_critical(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    // Use the critical keyword here!
    #pragma omp parallel for 
    for (int i = 0; i < arr_size; i++) {
        double value = x[i] * y[i];
        #pragma omp critical 
        {
            global_sum += x[i] * y[i];
        }
    }
    return global_sum;
}

// Reduction Keyword
double dotp_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    // Use the reduction keyword here!
    #pragma omp parallel for reduction (+:global_sum)
    for (int i = 0; i < arr_size; i++) {
        global_sum += x[i] * y[i];
    }
    return global_sum;
}

// Manual Reduction
double dotp_manual_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    // Do NOT use the `reduction` directive here!
    int thread_size = omp_get_max_threads();
    int block_size = arr_size / thread_size;
    #pragma omp parallel
    {
        // printf("bsize %d, tsize %d\n", block_size, thread_size);
        int base = omp_get_thread_num() * block_size;
        double local_sum = 0.0;
        // TODO: Parallel Section
        int end = omp_get_thread_num() == omp_get_max_threads() - 1 ? arr_size : (base + block_size);
        for (int i = base; i < end; i++) {
            local_sum += x[i] * y[i];
        }
        // TODO: Critical Section
        #pragma omp critical
        global_sum += local_sum;
    }
    return global_sum;
}
