#ifndef SIMD_UTILS_H
#define SIMD_UTILS_H

#include <immintrin.h>
#include <cmath>

// SIMD向量类型
typedef __m128 float4;

// 加载4个float到SIMD寄存器
inline float4 load4(const float* data) {
    return _mm_load_ps(data);
}

// 存储SIMD寄存器到4个float
inline void store4(float* data, float4 value) {
    _mm_store_ps(data, value);
}

// SIMD加法
inline float4 add4(float4 a, float4 b) {
    return _mm_add_ps(a, b);
}

// SIMD减法
inline float4 sub4(float4 a, float4 b) {
    return _mm_sub_ps(a, b);
}

// SIMD乘法
inline float4 mul4(float4 a, float4 b) {
    return _mm_mul_ps(a, b);
}

// SIMD标量乘法
inline float4 mul4_scalar(float4 a, float scalar) {
    float4 scalar_vec = _mm_set1_ps(scalar);
    return _mm_mul_ps(a, scalar_vec);
}

// SIMD点积
inline float dot4(float4 a, float4 b) {
    float4 mul = _mm_mul_ps(a, b);
    float4 shuffled = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
    float4 sum = _mm_add_ps(mul, shuffled);
    shuffled = _mm_shuffle_ps(sum, sum, _MM_SHUFFLE(1, 0, 3, 2));
    sum = _mm_add_ps(sum, shuffled);
    float result;
    _mm_store_ss(&result, sum);
    return result;
}

// SIMD长度平方
inline float length_squared4(float4 vec) {
    return dot4(vec, vec);
}

// SIMD长度
inline float length4(float4 vec) {
    return sqrtf(length_squared4(vec));
}

// SIMD归一化
inline float4 normalize4(float4 vec) {
    float len = length4(vec);
    if (len > 1e-6) {
        return mul4_scalar(vec, 1.0f / len);
    }
    return vec;
}

#endif // SIMD_UTILS_H
