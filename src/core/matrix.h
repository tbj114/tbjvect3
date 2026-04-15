#ifndef MATRIX_H
#define MATRIX_H

#include "geometry.h"

namespace geometry {

// 4x4矩阵类
class Matrix4x4 {
public:
    float data[4][4];
    
    Matrix4x4();
    Matrix4x4(float diagonal);
    
    // 矩阵运算
    Matrix4x4 operator*(const Matrix4x4& other) const;
    Vector3D operator*(const Vector3D& vector) const;
    
    // 矩阵变换
    static Matrix4x4 translation(const Vector3D& translation);
    static Matrix4x4 rotation(const Vector3D& eulerAngles);
    static Matrix4x4 rotation(float angle, const Vector3D& axis);
    static Matrix4x4 scale(const Vector3D& scale);
    
    // 矩阵操作
    Matrix4x4 transpose() const;
    Matrix4x4 inverse() const;
    float determinant() const;
};

// 四元数类
class Quaternion {
public:
    float w, x, y, z;
    
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(float angle, const Vector3D& axis);
    
    // 四元数运算
    Quaternion operator*(const Quaternion& other) const;
    Quaternion operator+(const Quaternion& other) const;
    Quaternion operator*(float scalar) const;
    
    // 四元数操作
    Quaternion conjugate() const;
    Quaternion inverse() const;
    float length() const;
    Quaternion normalize() const;
    
    // 转换
    Matrix4x4 toMatrix() const;
    Vector3D rotate(const Vector3D& vector) const;
};

} // namespace geometry

#endif // MATRIX_H
