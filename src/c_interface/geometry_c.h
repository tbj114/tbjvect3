#ifndef GEOMETRY_C_H
#define GEOMETRY_C_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// C兼容的三维向量结构
typedef struct {
    float x, y, z;
} Vector3D_C;

// C兼容的4x4矩阵结构
typedef struct {
    float data[4][4];
} Matrix4x4_C;

// C兼容的四元数结构
typedef struct {
    float w, x, y, z;
} Quaternion_C;

// 向量运算
Vector3D_C vector3d_add(Vector3D_C v1, Vector3D_C v2);
Vector3D_C vector3d_sub(Vector3D_C v1, Vector3D_C v2);
Vector3D_C vector3d_mul(Vector3D_C v, float scalar);
Vector3D_C vector3d_div(Vector3D_C v, float scalar);

// 点积
float vector3d_dot(Vector3D_C v1, Vector3D_C v2);

// 叉积
Vector3D_C vector3d_cross(Vector3D_C v1, Vector3D_C v2);

// 长度
float vector3d_length(Vector3D_C v);

// 归一化
Vector3D_C vector3d_normalize(Vector3D_C v);

// 三维投影
Vector3D_C vector3d_project(Vector3D_C vector, Vector3D_C axis);

// 分离轴定律 - 检测两个凸多边形是否碰撞
bool sat_collision(Vector3D_C* shape1, int shape1_size, Vector3D_C* shape2, int shape2_size);

// 闵可夫斯基差 - 返回结果的大小
int minkowski_difference(Vector3D_C* shape1, int shape1_size, Vector3D_C* shape2, int shape2_size, Vector3D_C* result);

// 凹形碰撞检测（通过凸分解）
bool concave_collision(Vector3D_C** shape1, int* shape1_sizes, int shape1_parts, Vector3D_C** shape2, int* shape2_sizes, int shape2_parts);

// 矩阵运算
Matrix4x4_C matrix4x4_multiply(Matrix4x4_C m1, Matrix4x4_C m2);
Vector3D_C matrix4x4_multiply_vector(Matrix4x4_C m, Vector3D_C v);

// 矩阵变换
Matrix4x4_C matrix4x4_translation(Vector3D_C translation);
Matrix4x4_C matrix4x4_rotation(Vector3D_C eulerAngles);
Matrix4x4_C matrix4x4_rotation_axis(float angle, Vector3D_C axis);
Matrix4x4_C matrix4x4_scale(Vector3D_C scale);

// 矩阵操作
Matrix4x4_C matrix4x4_transpose(Matrix4x4_C m);
Matrix4x4_C matrix4x4_inverse(Matrix4x4_C m);
float matrix4x4_determinant(Matrix4x4_C m);

// 四元数运算
Quaternion_C quaternion_multiply(Quaternion_C q1, Quaternion_C q2);
Quaternion_C quaternion_add(Quaternion_C q1, Quaternion_C q2);
Quaternion_C quaternion_multiply_scalar(Quaternion_C q, float scalar);

// 四元数操作
Quaternion_C quaternion_conjugate(Quaternion_C q);
Quaternion_C quaternion_inverse(Quaternion_C q);
float quaternion_length(Quaternion_C q);
Quaternion_C quaternion_normalize(Quaternion_C q);

// 四元数转换
Matrix4x4_C quaternion_to_matrix(Quaternion_C q);
Vector3D_C quaternion_rotate(Quaternion_C q, Vector3D_C v);

#ifdef __cplusplus
}
#endif

#endif // GEOMETRY_C_H
