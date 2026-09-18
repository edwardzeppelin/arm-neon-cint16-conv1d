#ifndef DSP_LECTURE_H
#define DSP_LECTURE_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <arm_acle.h>
#include <arm_neon.h>
#include <time.h>
#include <stdbool.h>

#define N_MAX 65535

typedef struct { int16_t real,imag; } cint16_t;
typedef struct { int32_t real,imag; } cint32_t;

void convolution_fast(int n, cint16_t* dst, const cint16_t* src1, const cint16_t* src2);
void convolution_ref(int n, cint16_t* dst, const cint16_t* src1, const cint16_t* src2);

#endif /* DSP_LECTURE_H */
