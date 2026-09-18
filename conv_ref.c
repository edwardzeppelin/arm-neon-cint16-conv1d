#include "dsp-lecture.h"

void convolution_ref(int n, cint16_t* dst, const cint16_t* src1, const cint16_t* src2) {
    for (int i = 0; i < 2 * n - 1; i++) {
        dst[i].real = 0;
        dst[i].imag = 0;

        for (int j = 0; j < n; j++) {
            int k = i - j;
            if (k >= 0 && k < n) {
                dst[i].real += src1[j].real * src2[k].real - src1[j].imag * src2[k].imag;
                dst[i].imag += src1[j].real * src2[k].imag + src1[j].imag * src2[k].real;
            }
        }
    }
}
