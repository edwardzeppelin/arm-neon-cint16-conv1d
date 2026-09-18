#include "dsp-lecture.h"

void convolution_fast(int n, cint16_t* dst, const cint16_t* src1, const cint16_t* src2) {
    assert(n > 0);

    // Инициализация dst нулями (размер результата: 2*n-1)
    for (int i = 0; i < 2 * n - 1; i++) {
        dst[i].real = 0;
        dst[i].imag = 0;
    }

    for (int i = 0; i < n; i++) {
        int j = 0;

        // Векторизованная часть
        for (; j <= n - 8; j += 8) {
            // Загружаем 8 комплексных чисел из src2
            int16x8x2_t src2_vec = vld2q_s16((int16_t*)&src2[j]);
            
            int16x8_t src1_real = vdupq_n_s16(src1[i].real);
            int16x8_t src1_imag = vdupq_n_s16(src1[i].imag);

            // Вычисляем real и imag части
            int16x8_t real_part1 = vmulq_s16(src1_real, src2_vec.val[0]); // real*real
            int16x8_t real_part2 = vmulq_s16(src1_imag, src2_vec.val[1]); // imag*imag
            int16x8_t real_result = vsubq_s16(real_part1, real_part2); // real*real - imag*imag
            
            int16x8_t imag_part1 = vmulq_s16(src1_real, src2_vec.val[1]); // real*imag
            int16x8_t imag_part2 = vmulq_s16(src1_imag, src2_vec.val[0]); // imag*real
            int16x8_t imag_result = vaddq_s16(imag_part1, imag_part2); // real*imag + imag*real

            // Преобразуем векторы в массивы для доступа по индексу
            int16_t real_arr[8], imag_arr[8];
            vst1q_s16(real_arr, real_result);
            vst1q_s16(imag_arr, imag_result);

            // Накопительное сложение
            for (int k = 0; k < 8; ++k) {
                int idx = i + j + k;
                dst[idx].real += real_arr[k];
                dst[idx].imag += imag_arr[k];
            }
        }

        // Скалярная часть для оставшихся элементов
        for (; j < n; j++) {
            int idx = i + j;
            dst[idx].real += src1[i].real * src2[j].real - src1[i].imag * src2[j].imag;
            dst[idx].imag += src1[i].real * src2[j].imag + src1[i].imag * src2[j].real;
        }
    }
}