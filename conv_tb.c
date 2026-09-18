#include "dsp-lecture.h"

void random_vector(int n, cint16_t* v) {
    for (int i = 0; i < n; i++) {
        v[i].real = rand() % 256;  // Ограничим значения для переполнения
        v[i].imag = rand() % 256;
    }
}

void convolution_tb(int16_t seed, int num_runs) {
    srand(seed);
    
    for (int run = 0; run < num_runs; run++) {
        int n = (rand() % (N_MAX - 1)) + 1;
        int dst_size = 2 * n - 1;
        
        cint16_t* src1 = (cint16_t*)malloc(n * sizeof(cint16_t));
        cint16_t* src2 = (cint16_t*)malloc(n * sizeof(cint16_t));
        cint16_t* dst_fast = (cint16_t*)calloc(dst_size, sizeof(cint16_t));
        cint16_t* dst_ref = (cint16_t*)calloc(dst_size, sizeof(cint16_t));

        assert(src1 != NULL && src2 != NULL && dst_fast != NULL && dst_ref != NULL);

        random_vector(n, src1);
        random_vector(n, src2);

        clock_t ref_start = clock();
        convolution_ref(n, dst_ref, src1, src2);
        clock_t ref_time = clock() - ref_start;
        printf("Ref time: %ld ticks\n", (long)ref_time);

        clock_t fast_start = clock();
        convolution_fast(n, dst_fast, src1, src2);
        clock_t fast_time = clock() - fast_start;
        printf("Fast time: %ld ticks\n", (long)fast_time);
     
        bool error = false;
        for (int i = 0; i < dst_size; i++) {
            if (dst_fast[i].real != dst_ref[i].real || dst_fast[i].imag != dst_ref[i].imag) {
                fprintf(stderr, "Error at index %d: ref=(%d, %d) fast=(%d, %d)\n", 
                        i, dst_ref[i].real, dst_ref[i].imag, dst_fast[i].real, dst_fast[i].imag);
                error = true;
                break;
            }
        }
        
        if (!error) {
            printf("Run %d: OK (n=%d, dst_size=%d)\n", run, n, dst_size);
        }

        free(src1);
        free(src2);
        free(dst_fast);
        free(dst_ref);
    }
}

int main() {
    convolution_tb(4711, 100);
    printf("Success\n");
    return 0;
}