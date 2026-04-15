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

#ifdef __cplusplus
}
#endif

#endif // GEOMETRY_C_H
