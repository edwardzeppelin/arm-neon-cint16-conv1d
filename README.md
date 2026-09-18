# ARM NEON 1D Complex Convolution

Performance benchmark and verification framework for 16-bit 1D complex vector convolution accelerated using **128-bit ARM NEON SIMD intrinsics** (`vld2q_s16`, `vdupq_n_s16`, `vmulq_s16`, `vsubq_s16`, `vaddq_s16`).

## Key Features
* **1D Complex Convolution**: Computes discrete convolution for complex 16-bit signals of length $n$, producing an output vector of size $2n - 1$.
* **128-Bit ARM NEON Acceleration**:
  * Processes 8 complex elements simultaneously using 128-bit NEON registers (`int16x8_t`, `int16x8x2_t`).
  * De-interleaves real and imaginary components of `src2` via `vld2q_s16`.
  * Broadcasts scalar real and imaginary parts of `src1[i]` across 8 vector lanes using `vdupq_n_s16`.
  * Computes complex products $(a + jb) \cdot (c + jd) = (ac - bd) + j(ad + bc)$ via `vmulq_s16`, `vsubq_s16`, and `vaddq_s16`.
* **Automated Benchmarking & Testing**: Features a testbench that measures execution time in CPU ticks (`clock()`) and validates fast SIMD output against scalar C reference calculations.

## Project Structure
* `conv_fast.c` — Fast 1D complex convolution using 128-bit ARM NEON SIMD intrinsics.
* `conv_ref.c` — Scalar reference C implementation of complex convolution.
* `conv_tb.c` — Automated benchmark testbench with randomized complex inputs and runtime measurement.
* `dsp-lecture.h` — Header defining `cint16_t` data structures and function prototypes.

## Build & Run

```bash
gcc -O2 -mfpu=neon conv_tb.c conv_fast.c conv_ref.c -o neon_conv_test
./neon_conv_test
```
