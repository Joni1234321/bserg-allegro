#pragma once
#include "mathb-types.h"
#include <cmath>
#include <immintrin.h>

template <typename T>
inline T lerp(T a, T b, float t) {
    //return b * t + a * (1 - t);
    return b * t + a * (1 - t);
}

template <size_t N>
inline int mask() {
    return ~(N - 1);
}

/// <summary>
/// Split n into normal iterations and simd iterations
/// </summary>
/// <param name="n"></param>
/// <param name="simdMoves">iterations over 256 simd instructions</param>
/// <param name="normalMoves">iterations over normal instructions, max value is 31 </param>
template <size_t N>
inline void splitN(size_t n, size_t& simdIterations, size_t& normalIterations) {
    static const size_t shifts = std::log2(N); // 5
    static const size_t normalMask = N - 1; // get everything below, 31
    simdIterations = n >> shifts;
    normalIterations = n & normalMask;
}

/*
inline void f4(const std::vector<float>& numbers, std::vector<float>& out) {
    {
        TIMER("SIMD");

        for (int i = 0; i < numbers.size(); i += 8) {
            __m256 x = _mm256_loadu_ps(&numbers[i]);
            __m256 y = _mm256_rsqrt_ps(x);
            for (int j = 0; j < 8; j++)
                y = _mm256_rsqrt_ps(y);

            _mm256_storeu_ps(&out[i], y);
        }
    }
    std::cout << numbers[0] << out[0] << "\n";
    std::cout << numbers[1] << out[1] << "\n";
}
*/


// Test static or const, as weel as constexpr for the constants 
// Check if they still are getting stored in the register, this could be neat if they deid. DIPSHIT
// Use FMA instruction to calcualate lerp

inline __m256 lerp256(__m256 a, __m256 b, const float t) {
    __m256 tplus = _mm256_set1_ps(t);
    __m256 tminus = _mm256_set1_ps(-t);
    return _mm256_fmadd_ps(tplus, b, _mm256_fmadd_ps(tminus, a, a));
}

inline __m256 lerp256(const float * a, const float * b, const float t) {
    __m256 regA = _mm256_loadu_ps(a);
    __m256 regB = _mm256_loadu_ps(b);

    //fma(t, v1, fma(-t, v0, v0))
    return lerp256(regA, regB, t);
}

inline void lerp256(const float* a, const float* b, const float t, float * out) {
    __m256 tplus = _mm256_set1_ps(t);
    __m256 tminus = _mm256_set1_ps(-t);

    __m256 regA = _mm256_loadu_ps(a);
    __m256 regB = _mm256_loadu_ps(b);

    __m256 val = _mm256_fmadd_ps(tplus, regB, _mm256_fmadd_ps(tminus, regA, regA));

    _mm256_storeu_ps(out, val);
}

inline float rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long*)&y;                       // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);               // what the fuck? 
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));   // 1st iteration
    //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}